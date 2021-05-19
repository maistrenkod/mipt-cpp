#include "Board.h"
#include <iostream>


Board::Board() : mBoardSize(8)
{
}


Board::~Board()
{
}

void Board::ResetMap()
{

	for (size_t i = 0; i < mBoardSize; i++)
	{
		for (size_t j = 0; j < mBoardSize; j++)
		{

			Cell::State state;
			int n = board[i][j];
			switch (n)
			{
			case 0:
				state = Cell::State::BLANKwhite;
				break;
			case 1:
				state = Cell::State::BLACK;
				break;
			case 2:
				state = Cell::State::WHITE;
				break;
			case 3:
				state = Cell::State::BLANKblack;
				break;
			}
			const pos position = pos(i, j);
			Cell cell = Cell(state);
			mCells.insert({ std::move(position), std::move(cell) });
		}
	}
}


Board::MoveResult Board::CheckMove(const pos& startPos, const pos& endPos, bool direction/*в зависимости от того какой сейчас игрок*/)
{
	Board::MoveResult result = Board::MoveResult::PROHIBITED;
	const int dY = endPos.first - startPos.first;
	const int dX = endPos.second - startPos.second;
	bool isCombat = false;

	if (dX == 0 && dY == 0 && endPos.first == 0 && endPos.second == 0)
	{
		result = Board::MoveResult::FF;
	}
	else if (endPos.first >= 0 && endPos.first < mBoardSize && endPos.second >= 0 && endPos.second < mBoardSize)
	{
		auto targetCellState = mCells.at(endPos).GetState();

		if (targetCellState == Cell::State::BLANKblack)
		{
			if (abs(dX) == 2 && abs(dY) == 2)
			{
				pos victimPos((startPos.first + endPos.first) / 2, (startPos.second + endPos.second) / 2);
				auto vistimCellState = mCells.at(victimPos).GetState();
				auto startCellState = mCells.at(startPos).GetState();

				result =
					targetCellState != vistimCellState && startCellState != vistimCellState ? Board::MoveResult::SUCCESSFUL_COMBAT : result;
			}
			else if ((abs(dX) == 1 && dY == 1 && direction) || (abs(dX) == 1 && dY == -1 && !direction))
			{
				result = Board::MoveResult::SUCCESSFUL_MOVE;
			}
		}
	}

	return result;
}


Board::MoveResult Board::MakeMove(const pos& startPos, const pos& endPos, bool direction)
{
	auto moveResult = CheckMove(startPos, endPos, direction);

	switch (moveResult)
	{
	case Board::MoveResult::SUCCESSFUL_MOVE:
		mCells.at(endPos).SetState(mCells.at(startPos).GetState());
		mCells.at(startPos).SetState(Cell::State::BLANKblack);
		break;
	case Board::MoveResult::SUCCESSFUL_COMBAT:
		mCells.at(endPos).SetState(mCells.at(startPos).GetState());
		mCells.at(startPos).SetState(Cell::State::BLANKblack);
		mCells.at(pos((startPos.first + endPos.first) / 2, (startPos.second + endPos.second) / 2)).SetState(Cell::State::BLANKblack);
		break;
	}
	
	return moveResult;
}

void Board::drawboard()
{
	mboardtexture.loadFromFile("images\\board.jpg");
	mboardsprite.setTexture(mboardtexture);

}

void Board::drawcells()
{
	pos position;
	for (size_t i = 0; i < mBoardSize; i++)
		for (size_t j = 0; j < mBoardSize; j++)
		{
			position = pos(i, j);
			mCells.at(position).draw();
			mCells.at(position).setSpritepos(indent + size * j, indent + size * i);
		}
}

void Board::drawOnWindow2(RenderWindow& window)
{
	window.draw(mboardsprite);
	for (auto cell : mCells)
	{
		cell.second.drawOnWindow(window);
	}
}

bool Board::morecheckers(pos currentpos)
{
	pos nextpos;
	nextpos.first = currentpos.first + 1;
	nextpos.second = currentpos.second + 1;
	if (mCells.at(nextpos).GetState() == Cell::State::BLANKblack) return true;
	nextpos.first = currentpos.first - 1;
	nextpos.second = currentpos.second + 1;
	if (mCells.at(nextpos).GetState() == Cell::State::BLANKblack) return true;
	nextpos.first = currentpos.first - 1;
	nextpos.second = currentpos.second - 1;
	if (mCells.at(nextpos).GetState() == Cell::State::BLANKblack) return true;
	nextpos.first = currentpos.first + 1;
	nextpos.second = currentpos.second - 1;
	if (mCells.at(nextpos).GetState() == Cell::State::BLANKblack) return true;
	return false;
}
