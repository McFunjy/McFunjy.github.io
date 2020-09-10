#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "map.h"

using namespace sf;
using namespace std;

class Enemy {
private: float x, y, w, h;
	   String File; //���� � �����������
public:
	float dx, dy, speed = 0.1, deathTimer = 0;
	int state = 0;
	bool life, isEnemy;
	Texture texture;//���� ��������
	Sprite sprite;
	Enemy(String F, float X, float Y, float W, float H)
	{
		File = F;//��� �����+���������
		life = true; isEnemy = true;
		w = W; h = H;//������ � ������
		texture.loadFromFile("images/" + File);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
		x = X; y = Y;//���������� ��������� �������
		sprite.setTextureRect(IntRect(3, 3, w, h));
	}

	void update(float time, float X, float Y) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		Run(X,Y);
		switch (state)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case 0: dx = speed; dy = 0; (isEnemy) ? sprite.setTextureRect(IntRect(3, 3, 42, 42)) : sprite.setTextureRect(IntRect(180, 3, 42, 42));  break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
		case 1: dx = -speed; dy = 0; (isEnemy) ? sprite.setTextureRect(IntRect(58, 3, 42, 42)) : sprite.setTextureRect(IntRect(235, 3, 42, 42)); break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
		case 2: dx = 0; dy = speed; (isEnemy) ? sprite.setTextureRect(IntRect(107, 3, 42, 42)) : sprite.setTextureRect(IntRect(284, 3, 42, 42)); break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
		case 3: dx = 0; dy = -speed; (isEnemy) ? sprite.setTextureRect(IntRect(107, 58, 42, 42)) : sprite.setTextureRect(IntRect(284, 55, 42, 42)); break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
		}

		x += dx * time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
		y += dy * time;//���������� �� ������

		//speed = 0;//�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
		
	}


	void Run(float px, float py)//�-��� �������������� � ������
	{
		if (isEnemy == true)
		{
			for (int i = y / 61; i < (y + h) / 61; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 61*61.
				for (int j = x / 61; j < (x + w) / 61; j++)//��� ����� �� 61, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
				{
					if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
					{
						if (dx > 0)
						{
							x = j * 61 - w-1;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
							if (y < py)state = 2; 
							else state = 3;
						}
						if (dx < 0)
						{
							x = j * 61 + 62;//���������� ���� �����
							if (y < py)state = 2;
							else state = 3;
						}
						if (dy > 0)//���� �� ��� ����,
						{
							y = i * 61 - h-1;
							if (x < px)state = 0;
							else state = 1;
						}
						if (dy < 0)
						{
							y = i * 61 + 62;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������
							if (x < px)state = 0;
							else state = 1;
						}

					}

				}
		}
		else
		{
			for (int i = y / 61; i < (y + h) / 61; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 61*61.
				for (int j = x / 61; j < (x + w) / 61; j++)//��� ����� �� 61, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
				{
					if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
					{
						if (dx > 0)
						{
							x = j * 61 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
							if (y < py)state = 3; else state = 2;
						}
						if (dx < 0)
						{
							x = j * 61 + 61;//���������� ���� �����
							if (y < py)state = 3; else state = 2;
						}
						if (dy > 0)//���� �� ��� ����,
						{
							y = i * 61 - h;
							if (x < px)state = 1; else state = 0;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
						}
						if (dy < 0)
						{
							y = i * 61 + 61;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������
							if (x < px)state = 1; else state = 0;
						}

					}

				}
		}
		
	}
	void checkDeath(float time)
	{
		if (deathTimer > 0)
		{
			deathTimer -= time * 700;
		}
		else if ((x == -42) && (y == -42) && (deathTimer <= 0))
		{
			life = true;
			speed = 0.1;
			x = 490;
			y = 554;
		}
	}
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
		float getenemycoordinateX() { return x; }
		float getenemycoordinateY() { return y; }
		float& setenemycoordinatex() { return x; }
		float& setenemycoordinatey() { return y; }
};


class Player { // ����� ������
private: float x, y, w, h;
	   String File; //���� � �����������
public:
	float dx, dy, speed=0, killTimer=0,CurrentFrame = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int state=0,Score=0; //����������� (direction) �������� ������
	bool life;
	Texture texture;//���� ��������
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) { //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		File = F;//��� �����+���������
		life = true; 
		w = W; h = H;//������ � ������
		texture.loadFromFile("images/" + File);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
		x = X; y = Y;//���������� ��������� �������
		sprite.setTextureRect(IntRect(9, 9, w, h)); //������ ������� ���� ������������� ��� ������ ������ �������, � �� ���� ������� �����. IntRect - ���������� �����
	};

	void control(float time)
	{
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			state = 1; speed = 0.13;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame = 0;
			sprite.setTextureRect(IntRect(12 + 49 * int(CurrentFrame), 62, 42, 42)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			state = 0; speed = 0.13;//����������� ������, �� ����
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame = 0;
			sprite.setTextureRect(IntRect(12 + 50 * int(CurrentFrame), 11, 42, 42)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			state = 3; speed = 0.13;//����������� ����, �� ����
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame = 0;
			sprite.setTextureRect(IntRect(12 + 50 * int(CurrentFrame), 161, 42, 42)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)

		}

		if (Keyboard::isKeyPressed(Keyboard::S)) { //���� ������ ������� ������� ����� ��� ���� ����� �
			state = 2; speed = 0.13;//����������� �����, �� ����
			CurrentFrame += 0.005 * time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame = 0; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			sprite.setTextureRect(IntRect(12 + 51 * int(CurrentFrame), 111, 42, 42)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96

		}
		update(time);
	}
	void update(float time) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		switch (state)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case 0: dx = speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
		case 1: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
		case 2: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
		case 3: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
		}

		x += dx * time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
		y += dy * time;//���������� �� ������

		speed = 0;//�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
		interactionWithMap();
	}
	float getplayercoordinateX(){	
return x;
}
float getplayercoordinateY(){
return y;
}
	void interactionWithMap()//�-��� �������������� � ������
	{

		for (int i = y / 61; i < (y + h) / 61; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 61*61.
			for (int j = x / 61; j < (x + w) / 61; j++)//��� ����� �� 61, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy > 0)//���� �� ��� ����,
					{
						y = i * 61 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					}
					if (dy < 0)
					{
						y = i * 61 + 61;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					}
					if (dx > 0)
					{
						x = j * 61 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					}
					if (dx < 0)
					{
						x = j * 61 + 61;//���������� ���� �����
					}
				}
				if (TileMap[i][j] == 's') {
					killTimer = 5000000;
				}
				if ((TileMap[i][j] == ' ')||(TileMap[i][j] == 's')) { //���� ������ ����� 's' (������)
					//x = 300; y = 300;//����� �� ��������... �������� ������������ �����
					TileMap[i][j] = '.';//������� ������, ���� ����� �����.
					Score++;
				}
				
				
			}
	}
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
};




void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/IGRAT.png");
	menuTexture2.loadFromFile("images/PRAVILA.png");
	menuTexture3.loadFromFile("images/VYKHOD.png");
	aboutTexture.loadFromFile("images/Rules.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture);
		bool isMenu = true;
	int menuNum = 0;
	menu1.setPosition(450, 300);
	menu2.setPosition(450, 400);
	menu3.setPosition(450, 500);
	about.setPosition(100, 100);
	while (isMenu)
	{
		menu1.setTextureRect(IntRect(0, 1, 332, 82));
		menu2.setTextureRect(IntRect(0, 0, 332, 82));
		menu3.setTextureRect(IntRect(0, 1, 332, 82));
		menuNum = 0;
		window.clear();

		if (IntRect(450, 300, 332, 82).contains(Mouse::getPosition(window))) { menu1.setTextureRect(IntRect(367, 0, 332, 82));  menuNum = 1; }
		if (IntRect(450, 400, 332, 82).contains(Mouse::getPosition(window))) { menu2.setTextureRect(IntRect(343, 1, 332, 82)); menuNum = 2; }
		if (IntRect(450, 500, 332, 82).contains(Mouse::getPosition(window))) { menu3.setTextureRect(IntRect(367, 0, 332, 82));  menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ������� �� ���� 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}




int main()
{
	bool end = false;
	int timer = 0;
	RenderWindow window(VideoMode(1150,900), "Pac-Man");
	menu(window);
	Font font;//����� 
	font.loadFromFile("19189.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setFillColor(Color::Green);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text.setStyle(Text::Bold);
	Texture map;//�������� �����
	map.loadFromFile("images/map.png");//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������
	Clock clock;
	Player p("hero.png", 250, 250, 42, 42);
	Enemy e("enemy.jpg",190,800,42,42);
	Enemy e1("enemy.jpg", 500, 400, 42, 42);
	Enemy e2("enemy.jpg", 800, 600, 42, 42);
	Event event;
	while (window.isOpen())
	{
		if ((p.life==true)&&(end==false)) 
		{
			float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
			timer += time;
			clock.restart(); //������������� �����
			if(p.killTimer>0)
			p.killTimer -= time;
			time = time / 700;
			p.control(time);
			e.update(time, p.getplayercoordinateX(), p.getplayercoordinateY());
			e1.update(time, p.getplayercoordinateX(), p.getplayercoordinateY());
			e2.update(time, p.getplayercoordinateX(), p.getplayercoordinateY());

			if (p.killTimer > 0) { e.isEnemy = false; e1.isEnemy = false; e2.isEnemy = false; }
			else { e.isEnemy = true; e1.isEnemy = true; e2.isEnemy = true; }

			if (e.isEnemy == true)
			{
				if ((e.getRect().intersects(p.getRect())) || (e1.getRect().intersects(p.getRect())) || (e2.getRect().intersects(p.getRect())))
					p.life = false;
			}
			else
			{
				if (e.getRect().intersects(p.getRect())) {e.setenemycoordinatex() =-42, e.setenemycoordinatey()=-42, e.speed = 0; e.life = false; p.Score += 5; e.deathTimer = 8000000; }
				if (e1.getRect().intersects(p.getRect())) {e1.setenemycoordinatex()=-42,  e1.setenemycoordinatey() = -42, e1.speed = 0; e1.life = false; p.Score += 5; e1.deathTimer = 8000000;}
				if (e2.getRect().intersects(p.getRect()))  { e2.setenemycoordinatex() =-42, e2.setenemycoordinatey() = -42, e2.speed = 0; e2.life = false; p.Score += 5; e2.deathTimer = 8000000;}
			}
			window.clear();
			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(190, 1, 61, 61)); //���� ��������� ������ ������, �� ������ 1� ���������
					if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(1, 1, 61, 61));//���� ��������� ������ s, �� ������ 2� ���������
					if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(126, 1, 61, 61));//���� ��������� ������ 0, �� ������ 3� ���������
					if ((TileMap[i][j] == '.')) s_map.setTextureRect(IntRect(55, 1, 61, 61));

					s_map.setPosition(j * 61, i * 61);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

					window.draw(s_map);//������ ���������� �� �����
				}
			ostringstream ScoreStr, TimerS, TimerM;    // �������� ����������
			ScoreStr << p.Score;
			TimerS << timer / 1000000;
			TimerM << timer / 10000 % 100;
			text.setString("Score: " + ScoreStr.str() + "\n" + "Time: " + TimerS.str() + "." + TimerM.str());//������ ������ ������

			text.setPosition(1, 1);//������ ������� ������, ����� ������
			window.draw(text);//����� ���� �����

			window.draw(p.sprite);
			

			e.checkDeath(time);
			e1.checkDeath(time);
			e2.checkDeath(time);

			if(e.life==true) window.draw(e.sprite);
			if (e1.life == true) window.draw(e1.sprite);
			if (e2.life == true) window.draw(e2.sprite);

			end = true;
			for (int i=0; i< HEIGHT_MAP;i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if ((TileMap[i][j] == ' ') || (TileMap[i][j] == 's')) end = false;
				}
			window.display();
		}
		if(!p.life)
		{
		
			window.clear();
			ostringstream ScoreStr, TimerS, TimerM;    // �������� ����������
			ScoreStr << p.Score;
			TimerS << timer / 1000000;
			TimerM << timer / 10000 % 100;
			text.setString("Game Over \n\nScore: " + ScoreStr.str() + "\n" + "Time: " + TimerS.str() + "." + TimerM.str());//������ ������ ������
			text.setPosition(500, 330);//������ ������� ������, ����� ������
			window.draw(text);
			window.display();

		}
		if (end)
		{
			
			window.clear();
			ostringstream ScoreStr, TimerS, TimerM;    // �������� ����������
			ScoreStr << p.Score;
			TimerS << timer / 1000000;
			TimerM << timer / 10000 % 100;
			text.setString("YOU ARE WIN!!! \n\nScore: " + ScoreStr.str() + "\n" + "Time: " + TimerS.str() + "." + TimerM.str());//������ ������ ������
			text.setPosition(500, 330);//������ ������� ������, ����� ������
			window.draw(text);
			window.display();
		}

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

	}

	return 0;
}