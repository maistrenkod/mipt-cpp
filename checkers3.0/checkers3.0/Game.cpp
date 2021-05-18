#include "Game.h"
#include <iostream>
#include <stdlib.h>


Game::Game() : mWhiteScore(0), mBlackScore(0), mLastPlayer(Player::NONE), bIsSurrender(false)
{

}


Game::~Game()
{
}

Game::Player Game::GetWinner() const
{
	Player winner(Player::NONE);

	if (bIsSurrender)
	{
		if (mLastPlayer == Player::WHITE)
		{
			winner = Player::BLACK;
		}
		else if (mLastPlayer == Player::BLACK)
		{
			winner = Player::WHITE;
		}
	}
	else
	{
		if (mWhiteScore == 12)
		{
			winner = Player::WHITE;
		}
		else if (mBlackScore == 12)
		{
			winner = Player::BLACK;
		}
	}

	return winner;
}

void Game::Start()
{
	RenderWindow window(VideoMode(570, 450), "Checkers");
	int num;
	num = menu(window);
	
	if (num == 1)
	{
		Start2(window);
	}
	if (num == 2)
	{
		Startbot(window);
	}
}

void Game::Start2(RenderWindow& window)
{
	mboard.ResetMap();
	
	bool isMousefirstpressed = false;
	bool isMousefollpressed = false;
	pos startMousepos;
	pos endMousepos1, endMousepos2;
	std::vector<pos> moves;
	Board::MoveResult moveResult(Board::MoveResult::PROHIBITED);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					if (isMousefirstpressed == false)
					{
						startMousepos = getNumberofcell(Mouse::getPosition(window) - Vector2i(indent, indent));
						mboard.GetMap().at(startMousepos).changeColor(Color(0, 150, 150));
						moves.push_back(startMousepos);
						isMousefirstpressed = true;
					}
					else if (isMousefollpressed == false)//2click
					{
						endMousepos1 = getNumberofcell(Mouse::getPosition(window) - Vector2i(indent, indent));
						isMousefollpressed = true;
					} 
					else
					{					//if (isMousefirstpressed == true && isMousefollpressed == true)//3 click
						endMousepos2 = getNumberofcell(Mouse::getPosition(window) - Vector2i(indent, indent));
						moves.push_back(endMousepos2);
						if (endMousepos1 == endMousepos2)
						{
							mboard.GetMap().at(startMousepos).changeColor(Color(255, 255, 255));
							bool direction = GetDirection();
							for (int i = 1; i < moves.size(); i++)
							{
								//moveResult = mboard.CheckMove(moves[i], moves[i + 1], direction);
								moveResult = mboard.MakeMove(moves.at(i - 1), moves.at(i), direction);
								std::cout << moves.at(i - 1).first << "," << moves.at(i - 1).second << std::endl;
								std::cout << moves.at(i).first << "," << moves.at(i).second << std::endl;
								if (moveResult == Board::MoveResult::SUCCESSFUL_COMBAT)
								{
										UpdateScore();
								}
							}
							if (moveResult != Board::MoveResult::PROHIBITED)
							{
								SwitchPlayer();
							}
							
							moves.clear();

							isMousefirstpressed = false;
							isMousefollpressed = false;
						}
						else
						{
							endMousepos1 = endMousepos2;
						}
		
					}
						
				}

			
		}
		// Отрисовка окна
		window.clear();
		mboard.drawboard();
		mboard.drawcells();
		mboard.drawOnWindow2(window);
		mIO.PrintScore(mWhiteScore, mBlackScore, window);
		drawCurrentPlayer(window);
		if (GetWinner() != Player::NONE)
		{
			EndGame(GetWinner(), window);
		}
		window.display();
		
	}

	
}

void Game::Startbot(RenderWindow& window)
{
}

std::pair<size_t, size_t> Game::getNumberofcell(Vector2i a)
{
	std::pair<size_t, size_t> p;
	p.first = a.y / 50;
	p.second = a.x / 50;
	return p;
}


int Game::menu(RenderWindow& window)
{
	Texture menuTexture2, menuTexturecoomp, menuTexturerul, menuTexturepro, menuTextureexit, aboutTexture, menuBackground;
	menuTexture2.loadFromFile("D:\\graphics\\image-23.png");
	menuTexturecoomp.loadFromFile("D:\\graphics\\image-22.png");
	menuTexturerul.loadFromFile("D:\\graphics\\image-24.png");
	menuTexturepro.loadFromFile("D:\\graphics\\image-27.png");
	menuTextureexit.loadFromFile("D:\\graphics\\image-26.png");
	aboutTexture.loadFromFile("D:\\graphics\\new\\about.png");
	menuBackground.loadFromFile("D:\\graphics\\cher.jpg");
	Sprite menu2(menuTexture2), menucommp(menuTexturecoomp), menuril(menuTexturerul), menupro(menuTexturepro), menuexit(menuTextureexit), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu2.setPosition(30, 30 + 50);
	menucommp.setPosition(30, 90 + 50);
	menuril.setPosition(30, 150 + 50);
	menupro.setPosition(30, 210 + 50);
	menuexit.setPosition(30, 270 + 50);
	menuBg.setPosition(340, 0);

	while (isMenu)
	{
		menu2.setColor(Color::White);//1
		menucommp.setColor(Color::White);//2
		menuril.setColor(Color::White);//3
		menupro.setColor(Color::White);//4
		menuexit.setColor(Color::White);//5
		menuNum = 0;
		window.clear(Color(160, 10, 17));

		if (IntRect(30, 30 + 50, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color(0, 0, 0)); menuNum = 1; }
		if (IntRect(30, 90 + 50, 300, 50).contains(Mouse::getPosition(window))) { menucommp.setColor(Color(0, 0, 0)); menuNum = 2; }
		if (IntRect(30, 150 + 50, 300, 50).contains(Mouse::getPosition(window))) { menuril.setColor(Color(0, 0, 0)); menuNum = 3; }
		if (IntRect(30, 210 + 50, 300, 50).contains(Mouse::getPosition(window))) { menupro.setColor(Color(0, 0, 0)); menuNum = 4; }
		if (IntRect(30, 270 + 50, 300, 50).contains(Mouse::getPosition(window))) { menuexit.setColor(Color(0, 0, 0)); menuNum = 5; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 3) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 4) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 5) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu2);
		window.draw(menucommp);
		window.draw(menuril);
		window.draw(menupro);
		window.draw(menuexit);

		window.display();
	}
	return menuNum;
}

void Game::drawCurrentPlayer(RenderWindow& window)
{
	Font font;//шрифт 
	font.loadFromFile("D:\\graphics\\CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
	Text text("о", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	if (mLastPlayer == Player::WHITE)
	{
		text.setString("Ход чёрных");//задает строку тексту

	}
	else
	{
		text.setString("Ход белых");//задает строку тексту

	}
	text.setPosition(460, 10);//задаем позицию текста
	window.draw(text);
}

void Game::EndGame(Player player, RenderWindow& window)
{
	Font font;//шрифт 
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

}

bool Game::GetDirection() const
{
	bool direction;

	switch (mLastPlayer)
	{
	case Player::WHITE:
		direction = false;
		break;
	default:
		direction = true;
		break;
	}

	return direction;
}

movePos Game::MakeIO()
{
	// Print board
	//system("cls");
	//mIO.PrintScore(mWhiteScore, mBlackScore);
	//auto map = mboard.GetMap();
	//mIO.DrawBoard(map);

	// Ask for a move
	auto newMove = mIO.GetMove(GetCurrentPlayer());

	return std::move(newMove);
}

void Game::SwitchPlayer()
{
	if (mLastPlayer == Player::WHITE)
	{
		mLastPlayer = Player::BLACK;
	}
	else
	{
		mLastPlayer = Player::WHITE;
	}
}

void Game::UpdateScore()
{
	if (mLastPlayer == Player::WHITE)
	{
		mBlackScore++;
	}
	else
	{
		mWhiteScore++;
	}
}

std::string Game::GetCurrentPlayer() const
{
	std::string player;

	if (mLastPlayer == Player::WHITE)
	{
		player = "Black";
	}
	else
	{
		player = "White";
	}

	return std::move(player);
}

/*std::string Game::CastPlayer(Player player) const
{
	std::string playerStr;

	switch (player)
	{
	case Player::WHITE:
		playerStr = "White player";
		break;
	default:
		playerStr = "Black player";
		break;
	}

	return playerStr;
}*/
