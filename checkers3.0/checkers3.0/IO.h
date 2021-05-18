#pragma once

#include <utility>
#include <map>
#include "Cell.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <sstream>

using namespace sf;
using movePos = std::pair<pos, pos>;
using map = std::map<pos, Cell>;

class IO
{
public:
	IO();
	~IO();
	movePos GetMove(std::string player);
	void DrawBoard(const map& board);
	void PrintScore(size_t whiteScore, size_t blackScore, RenderWindow& window);
	//void EndGame(Game::Player player, RenderWindow& window);
	//void drawboard(const Board& board);
private:
	std::string CastState(Cell::State state);
	const int boardSize = 8;
};



