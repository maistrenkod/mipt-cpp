#include "IO.h"

#include <iostream>
#include <string>
#include <algorithm>


IO::IO()
{
}


IO::~IO()
{
}


movePos IO::GetMove(std::string player)
{
	movePos position;
	/*size_t p1, p2;
	std::string line1, line2;
	bool isLine1Number = true, isLine2Number = true;

	std::cout << player << " move:" << std::endl;

	std::cin >> line1;
	std::cin >> line2;

	std::for_each(line1.cbegin(), line1.cend(), [&](char c) { if (!isdigit(c)) isLine1Number = false; });
	std::for_each(line2.cbegin(), line2.cend(), [&](char c) { if (!isdigit(c)) isLine2Number = false; });

	if (!isLine1Number || !isLine2Number)
	{
		if (line1 == "ff")
		{
			// 00 00 move is a surrender
			position.first.first = 0;
			position.first.second = 0;
			position.second.first = 0;
			position.second.second = 0;
		}
		else
		{
			// 11 11 move is a bad user input
			position.first.first = 1;
			position.first.second = 1;
			position.second.first = 1;
			position.second.second = 1;
		}
	}
	else
	{
		p1 = (size_t)std::stoi(line1);
		p2 = (size_t)std::stoi(line2);



		position.first.first = p1 / 10;
		position.first.second = p1 - 10 * position.first.first;

		position.second.first = p2 / 10;
		position.second.second = p2 - 10 * position.second.first;
	}*/

	//position.first = mgrafic.p1;
	//position.second = mgrafic.p2;

	return std::move(position);
}


void IO::DrawBoard(const map& board)
{
	size_t boardSize = static_cast<size_t>(sqrt(board.size()));

	for (size_t i = 0; i < boardSize; i++)
	{
		std::cout << "|";

		for (size_t j = 0; j < boardSize; j++)
		{
			std::string cellValue = CastState(board.at(pos(i, j)).GetState());
			std::cout << cellValue;
			std::cout << "|";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;
}

void IO::PrintScore(size_t whiteScore, size_t blackScore, RenderWindow& window)
{
	Font font;//шрифт 
	font.loadFromFile("D:\\graphics\\CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
	Text text("о", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	std::ostringstream scoreWh;
	scoreWh << whiteScore;
	std::ostringstream scoreBl;
	scoreBl << blackScore;
	text.setString("Белые: " + scoreWh.str() + "\n\n\n\n" + "Чёрные: " + scoreBl.str());//задает строку тексту
	text.setPosition(460, 150);//задаем позицию текста
	window.draw(text);
}

/*void IO::EndGame(Game::Player player, RenderWindow& window)
{
	/*Font font;//шрифт 
	font.loadFromFile("D:\\graphics\\CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setOutlineColor(Color(255, 0, 0)); //покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	switch (player)
	{
	case Game::Player::BLACK:
		text.setString("Игра окончена!/nВыиграли чёрные!");//задает строку тексту
		break;
	case Game::Player::WHITE:
		text.setString("Игра окончена!/nВыиграли белые!");//задает строку тексту
		break;
	default:
		break;
	}
	text.setPosition(200, 200);//задаем позицию текста, центр камеры
	
	window.draw(text);
}*/


std::string IO::CastState(Cell::State state)
{
	std::string result;

	switch (state)
	{
	case Cell::State::BLACK:
		result = "B";
		break;
	case Cell::State::WHITE:
		result = "W";
		break;
	default:
		result = " ";
		break;
	}

	return std::move(result);
}

