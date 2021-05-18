#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include "Board.h"
#include "Cell.h"
#include <map>

using namespace sf;
using map = std::map<pos, Cell>;

class Grafic
{
public:
	Sprite sprite_figurines[24];
	//Vector2f offset;

	const int size = 50;

	int board[8][8] =
	{
		0,2,0,2,0,2,0,2,
		2,0,2,0,2,0,2,0,
		0,2,0,2,0,2,0,2,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		1,0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,1,
		1,0,1,0,1,0,1,0,
	};

	std::pair<size_t, size_t> p1;
	std::pair<size_t, size_t> p2;

	static std::pair<size_t, size_t> getNumberofcell(Vector2i a);
	void start_grafic();
	Grafic();
	void set_p1(std::pair<size_t, size_t> a);
	void set_p2(std::pair<size_t, size_t> a);
	std::pair<size_t, size_t> get_p1();
	std::pair<size_t, size_t> get_p2();
	void drawBoard(const map& board);

	RenderWindow window;
	Texture texture_board;
	Sprite sprite_board;
};

