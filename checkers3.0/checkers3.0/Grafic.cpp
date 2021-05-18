#include "Grafic.h"

Grafic::Grafic()
{

	RenderWindow window(VideoMode(450, 450), "Chekers");
	Sprite sprite_board(texture_board);

	/*offset.x = 22;
	offset.y = 22;*/
}

void Grafic::set_p1(std::pair<size_t, size_t> a)
{
	p1.first = a.first;
	p1.second = a.second;
}

void Grafic::set_p2(std::pair<size_t, size_t> a)
{
	p2.first = a.first;
	p2.second = a.second;
}

std::pair<size_t, size_t> Grafic::get_p1()
{
	return p1;
}

std::pair<size_t, size_t> Grafic::get_p2()
{
	return p2;
}

void Grafic::drawBoard(const map& board)
{
}

std::pair<size_t, size_t> Grafic::getNumberofcell(Vector2i a)
{
	std::pair<size_t, size_t> p;
	p.first = a.y / 50;
	p.second = a.x / 50;
	return p;
}

void Grafic::start_grafic()
{
	

	//Texture texture_board;
	texture_board.loadFromFile("D:\\graphics\\board.jpg");
	
	Font font;//шрифт 
	font.loadFromFile("D:\\graphics\\CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	text.setString("Собрано камней:");//задает строку тексту
	text.setPosition(200, 200);//задаем позицию текста, центр камеры
	window.draw(text);//рисую этот текст

	Texture texture_figurines;
	texture_figurines.loadFromFile("D:\\graphics\\figurines.png");
	for (int i = 0; i < 24; i++)
	{
		sprite_figurines[i].setTexture(texture_figurines);
	}

	int k = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			int n = board[i][j];
			if (n == 0) continue;
			if (n == 1)
			{
				sprite_figurines[k].setTextureRect(IntRect((n - 1) * size, 0, size, size));
				sprite_figurines[k].setPosition(22 + size * j, 22 + size * i);
			}
			if (n == 2)
			{
				sprite_figurines[k].setTextureRect(IntRect((n - 1) * size, 0, size, size));
				sprite_figurines[k].setPosition(22 + size * j, 22 + size * i);
			}
			k++;
		}

	bool isMove = false;
	float dx = 0, dy = 0;
	Vector2f oldPos, newPos;
	std::string str;
	int n = 0;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window) - Vector2i(22, 22);
		p1 = getNumberofcell(pos);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					for (int i = 0; i < 24; i++)
						if (sprite_figurines[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							isMove = true;
							n = i;
							dx = pos.x - sprite_figurines[i].getPosition().x;
							dy = pos.y - sprite_figurines[i].getPosition().y;
						}

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{
					isMove = false;
					Vector2f p = sprite_figurines[n].getPosition() + Vector2f(size / 2 - 22, size / 2 - 22);
					newPos = Vector2f(size * int(p.x / size) + 22, size * int(p.y / size) + 22);
					sprite_figurines[n].setPosition(newPos);
					sprite_figurines[n].setColor(Color::White);
				}
		}

		//if (dx > 60 && dy > 60) isMove = false;

		if (isMove)
		{
			sprite_figurines[n].setPosition(pos.x - dx, pos.y - dy);
			sprite_figurines[n].setColor(Color(128, 128, 128));
			Vector2i a(pos.x - dx, pos.y - dy);
			p2 = getNumberofcell(a);
		}

		window.draw(sprite_board);

		for (int i = 0; i < 24; i++)
		{
			window.draw(sprite_figurines[i]);
		}

		window.display();
	}
}
