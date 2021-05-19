#pragma once
#include "Board.h"
#include "IO.h"
#include "Checkers_bot.h"
#include "Transformer.h"
#include <functional>

using movePos = std::pair<pos, pos>;

class Game
{
public:
	enum class Player { NONE, BLACK, WHITE };
	const int indent = 24;
	Game();
	~Game();
	Player GetWinner() const;
	void Start();
	static std::pair<size_t, size_t> getNumberofcell(Vector2i a);
private:
	std::vector<pos> tranf(turn::Turn tr);
	int menu(RenderWindow& window);
	void drawCurrentPlayer(RenderWindow& window);
	void EndGame(Player player, RenderWindow& window);
	bool GetDirection() const;
	movePos MakeIO();
	void SwitchPlayer();
	void UpdateScore();
	void Start2(RenderWindow& window);
	void Startbot(RenderWindow& window);
	std::string GetCurrentPlayer() const;
	//std::string CastPlayer(Player player) const;
	size_t mWhiteScore;
	size_t mBlackScore;
	Player mLastPlayer;
	bool bIsSurrender;
	Board mboard;
	IO mIO;
};


