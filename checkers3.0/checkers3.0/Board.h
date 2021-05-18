#pragma once

#include "Cell.h"
#include <map>
#include <SFML/Graphics.hpp>

using map = std::map<pos, Cell>;
using namespace sf;

class Board
{
public:
	const int size = 50;
	const int indent = 24;
	int board[8][8] = //2-chwhite, 1- chblack,0 - white, 3 - black 
	{
		0,2,0,2,0,2,0,2,
		2,0,2,0,2,0,2,0,
		0,2,0,2,0,2,0,2,
		3,0,3,0,3,0,3,0,
		0,3,0,3,0,3,0,3,
		1,0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,1,
		1,0,1,0,1,0,1,0,
	};
	enum class MoveResult { SUCCESSFUL_MOVE, SUCCESSFUL_COMBAT, PROHIBITED, FF };
	Board();
	~Board();
	void ResetMap();
	MoveResult MakeMove(const pos& startPos, const pos& endPos, bool direction);
	map& GetMap() { return mCells; }
	void drawboard();
	void drawcells();
	void drawOnWindow2(RenderWindow& window);
	bool morecheckers(pos currentpos);
	MoveResult CheckMove(const pos& startPos, const pos& endPos, bool direction);
private:
	const size_t mBoardSize;
	map mCells;
	Texture mboardtexture;
	Sprite mboardsprite;
};

