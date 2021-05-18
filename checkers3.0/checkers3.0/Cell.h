#pragma once

#include <utility>
#include <SFML/Graphics.hpp>

using pos = std::pair<size_t, size_t>;
using namespace sf;

class Cell
{
public:
	enum class State { BLACK, WHITE, BLANKwhite, BLANKblack };
	const int indent = 24;
	Cell(State state);
	~Cell();
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	void draw();
	const int cellsize = 50;
	void setSpritepos(float x, float y);
	bool is_mouse_this(sf::RenderWindow& window) const;
	void changeColor(Color cl);
	void drawOnWindow(RenderWindow& window);
private:
	State mState;
	Sprite msprite;
	Texture mtexture;
};

