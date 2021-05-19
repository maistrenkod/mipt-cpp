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
	RenderWindow window(VideoMode(570, 450), "Simple checkers");
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
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
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
		// ��������� ����
		window.clear(Color(160, 10, 17));
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
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				window.close();
			if (mLastPlayer == Player::WHITE)
			{
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
									std::cout << moves.at(i - 1).first << "p" << moves.at(i - 1).second << std::endl;
									std::cout << moves.at(i).first << "p" << moves.at(i).second << std::endl;
									if (moveResult == Board::MoveResult::SUCCESSFUL_COMBAT)
									{
										UpdateScore();
									}
								}
								if (moveResult != Board::MoveResult::PROHIBITED)
								{
									//if (mLastPlayer == Game::Player::BLACK) std::cout << "yes\n";
									SwitchPlayer();
									//if (mLastPlayer == Game::Player::BLACK) std::cout << "yes\n";
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
		
			else
			{
				auto mp = mboard.GetMap();
				auto ar = tf::transformate_info(mp);
				auto best_turn = ch_bot::get_the_best_turn(ar, gotg::VALUES_FOR_FIELD::MY_CHECKERS, 2, [](bt::Eaten_checkers chek) -> double {return static_cast<double>(chek.count_of_enemy_cheakers) - static_cast<double>(chek.count_of_my_cheakers); });
				auto botmoves = tranf(best_turn);
				std::cout << best_turn << std::endl;
				bool direction = GetDirection();
				for (int i = 1; i < botmoves.size(); i++)
				{
					//moveResult = mboard.CheckMove(moves[i], moves[i + 1], direction);
					moveResult = mboard.MakeMove(botmoves.at(i - 1), botmoves.at(i), direction);
					std::cout << botmoves.at(i - 1).first << "b" << botmoves.at(i - 1).second << std::endl;
					std::cout << botmoves.at(i).first << "b" << botmoves.at(i).second << std::endl;
					if (moveResult == Board::MoveResult::SUCCESSFUL_COMBAT)
					{
						UpdateScore();
					}
				}
				botmoves.clear();
				SwitchPlayer();
				continue;
			}



		}
		// ��������� ����
		window.clear(Color(160, 10, 17));
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

std::pair<size_t, size_t> Game::getNumberofcell(Vector2i a)
{
	std::pair<size_t, size_t> p;
	p.first = a.y / 50;
	p.second = a.x / 50;
	return p;
}


std::vector<pos> Game::tranf(turn::Turn tr)
{
	std::vector<pos> result;
	pos a(11, 52);
	for (auto& t : tr.get_full_turn())
	{
		a.first = t.get_from().y;
		a.second = t.get_from().x;
		result.push_back(a);
	}
	a.first = tr.get_full_turn().back().get_to().y;
	a.second = tr.get_full_turn().back().get_to().x;
	result.push_back(a);
	return result;
}

int Game::menu(RenderWindow& window)
{
	Texture menuTexture2, menuTexturecoomp, menuTexturerul, menuTexturepro, menuTextureexit, proTexture, rulTexture, menuBackground;
	menuTexture2.loadFromFile("images\\image-23.png");
	menuTexturecoomp.loadFromFile("images\\image-22.png");
	menuTexturerul.loadFromFile("images\\image-24.png");
	menuTexturepro.loadFromFile("images\\image-27.png");
	menuTextureexit.loadFromFile("images\\image-26.png");
	proTexture.loadFromFile("images\\abouut.jpg");
	rulTexture.loadFromFile("images\\ruless.jpg");
	menuBackground.loadFromFile("images\\cher.jpg");
	Sprite menu2(menuTexture2), menucommp(menuTexturecoomp), menuril(menuTexturerul), menupro(menuTexturepro), menuexit(menuTextureexit), rul(rulTexture), pro(proTexture), menuBg(menuBackground);
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
			if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ������� �� ���� 
			if (menuNum == 2) isMenu = false;//���� ������ ������ ������, �� ������� �� ���� 
			if (menuNum == 3) { window.draw(rul); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 4) { window.draw(pro); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
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
	Font font;//����� 
	font.loadFromFile("images\\CyrilicOld.TTF");//�������� ������ ������ ���� ������
	Text text("�", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������

	if (mLastPlayer == Player::WHITE)
	{
		text.setString("��� ������");//������ ������ ������

	}
	else
	{
		text.setString("��� �����");//������ ������ ������

	}
	text.setPosition(460, 10);//������ ������� ������
	window.draw(text);
}

void Game::EndGame(Player player, RenderWindow& window)
{
	Font font;//����� 
	font.loadFromFile("images\\CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setOutlineColor(Color(255, 0, 0)); //��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	switch (player)
	{
	case Game::Player::BLACK:
		text.setString("���� ��������!/n�������� ������!");//������ ������ ������
		break;
	case Game::Player::WHITE:
		text.setString("���� ��������!/n�������� �����!");//������ ������ ������
		break;
	default:
		break;
	}
	text.setPosition(200, 200);//������ ������� ������, ����� ������

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
		return;
	}
	if (mLastPlayer == Player::BLACK)
	{
		mLastPlayer = Player::WHITE;
		return;
	}
	if (mLastPlayer == Player::NONE)
	{
		mLastPlayer = Player::WHITE;
		return;
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
