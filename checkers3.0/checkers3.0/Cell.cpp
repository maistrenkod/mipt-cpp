#include "Cell.h"


Cell::Cell(/*const pos & position,*/ State state) : /*mPosition(position),*/ mState(state)
{
}

Cell::~Cell()
{
}

void Cell::draw()
{
	mtexture.loadFromFile("D:\\graphics\\allcells1.png");
	msprite.setTexture(mtexture);
	switch (mState)
	{
	case Cell::State::BLACK:
		msprite.setTextureRect(IntRect(0 * cellsize, 0, cellsize, cellsize));
		break;
	case Cell::State::WHITE:
		msprite.setTextureRect(IntRect(1 * cellsize, 0, cellsize, cellsize));
		break;
	case Cell::State::BLANKwhite:
		msprite.setTextureRect(IntRect(2 * cellsize, 0, cellsize, cellsize));
		break;
	case Cell::State::BLANKblack:
		msprite.setTextureRect(IntRect(3 * cellsize, 0, cellsize, cellsize));
		//msprite.setColor(Color(0, 0, 0));
		break;
	default:
		break;
	}
}

void Cell::setSpritepos(float x, float y)
{
	msprite.setPosition(x, y);
}

bool Cell::is_mouse_this(sf::RenderWindow& window) const
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window) - Vector2i(indent, indent);
	if (msprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
	{
		return true;
	}
	return false;
}

void Cell::changeColor(Color cl)
{
	msprite.setColor(cl);
}

void Cell::drawOnWindow(RenderWindow& window)
{
	window.draw(msprite);
}

