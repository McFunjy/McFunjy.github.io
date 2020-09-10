#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "map.h"

using namespace sf;
using namespace std;

class Enemy {
private: float x, y, w, h;
	   String File; //файл с расширением
public:
	float dx, dy, speed = 0.1, deathTimer = 0;
	int state = 0;
	bool life, isEnemy;
	Texture texture;//сфмл текстура
	Sprite sprite;
	Enemy(String F, float X, float Y, float W, float H)
	{
		File = F;//имя файла+расширени
		life = true; isEnemy = true;
		w = W; h = H;//высота и ширина
		texture.loadFromFile("images/" + File);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(3, 3, w, h));
	}

	void update(float time, float X, float Y) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		Run(X,Y);
		switch (state)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0; (isEnemy) ? sprite.setTextureRect(IntRect(3, 3, 42, 42)) : sprite.setTextureRect(IntRect(180, 3, 42, 42));  break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0; (isEnemy) ? sprite.setTextureRect(IntRect(58, 3, 42, 42)) : sprite.setTextureRect(IntRect(235, 3, 42, 42)); break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0; dy = speed; (isEnemy) ? sprite.setTextureRect(IntRect(107, 3, 42, 42)) : sprite.setTextureRect(IntRect(284, 3, 42, 42)); break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed; (isEnemy) ? sprite.setTextureRect(IntRect(107, 58, 42, 42)) : sprite.setTextureRect(IntRect(284, 55, 42, 42)); break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		}

		x += dx * time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
		y += dy * time;//аналогично по игреку

		//speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		
	}


	void Run(float px, float py)//ф-ция взаимодействия с картой
	{
		if (isEnemy == true)
		{
			for (int i = y / 61; i < (y + h) / 61; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 61*61.
				for (int j = x / 61; j < (x + w) / 61; j++)//икс делим на 61, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
				{
					if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
					{
						if (dx > 0)
						{
							x = j * 61 - w-1;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
							if (y < py)state = 2; 
							else state = 3;
						}
						if (dx < 0)
						{
							x = j * 61 + 62;//аналогично идем влево
							if (y < py)state = 2;
							else state = 3;
						}
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 61 - h-1;
							if (x < px)state = 0;
							else state = 1;
						}
						if (dy < 0)
						{
							y = i * 61 + 62;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта
							if (x < px)state = 0;
							else state = 1;
						}

					}

				}
		}
		else
		{
			for (int i = y / 61; i < (y + h) / 61; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 61*61.
				for (int j = x / 61; j < (x + w) / 61; j++)//икс делим на 61, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
				{
					if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
					{
						if (dx > 0)
						{
							x = j * 61 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
							if (y < py)state = 3; else state = 2;
						}
						if (dx < 0)
						{
							x = j * 61 + 61;//аналогично идем влево
							if (y < py)state = 3; else state = 2;
						}
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 61 - h;
							if (x < px)state = 1; else state = 0;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 61 + 61;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта
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


class Player { // класс Игрока
private: float x, y, w, h;
	   String File; //файл с расширением
public:
	float dx, dy, speed=0, killTimer=0,CurrentFrame = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int state=0,Score=0; //направление (direction) движения игрока
	bool life;
	Texture texture;//сфмл текстура
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) { //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		File = F;//имя файла+расширени
		life = true; 
		w = W; h = H;//высота и ширина
		texture.loadFromFile("images/" + File);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(9, 9, w, h)); //Задаем спрайту один прямоугольник для вывода одного пакмена, а не кучи пакмена сразу. IntRect - приведение типов
	};

	void control(float time)
	{
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			state = 1; speed = 0.13;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame = 0;
			sprite.setTextureRect(IntRect(12 + 49 * int(CurrentFrame), 62, 42, 42)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			state = 0; speed = 0.13;//направление вправо, см выше
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame = 0;
			sprite.setTextureRect(IntRect(12 + 50 * int(CurrentFrame), 11, 42, 42)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			state = 3; speed = 0.13;//направление вниз, см выше
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame = 0;
			sprite.setTextureRect(IntRect(12 + 50 * int(CurrentFrame), 161, 42, 42)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

		}

		if (Keyboard::isKeyPressed(Keyboard::S)) { //если нажата клавиша стрелка влево или англ буква А
			state = 2; speed = 0.13;//направление вверх, см выше
			CurrentFrame += 0.005 * time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame = 0; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			sprite.setTextureRect(IntRect(12 + 51 * int(CurrentFrame), 111, 42, 42)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

		}
		update(time);
	}
	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (state)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		}

		x += dx * time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
		y += dy * time;//аналогично по игреку

		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		interactionWithMap();
	}
	float getplayercoordinateX(){	
return x;
}
float getplayercoordinateY(){
return y;
}
	void interactionWithMap()//ф-ция взаимодействия с картой
	{

		for (int i = y / 61; i < (y + h) / 61; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 61*61.
			for (int j = x / 61; j < (x + w) / 61; j++)//икс делим на 61, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)//если мы шли вниз,
					{
						y = i * 61 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy < 0)
					{
						y = i * 61 + 61;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					}
					if (dx > 0)
					{
						x = j * 61 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 61 + 61;//аналогично идем влево
					}
				}
				if (TileMap[i][j] == 's') {
					killTimer = 5000000;
				}
				if ((TileMap[i][j] == ' ')||(TileMap[i][j] == 's')) { //если символ равен 's' (камень)
					//x = 300; y = 300;//какое то действие... например телепортация героя
					TileMap[i][j] = '.';//убираем камень, типа взяли бонус.
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
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
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
	Font font;//шрифт 
	font.loadFromFile("19189.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setFillColor(Color::Green);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(Text::Bold);
	Texture map;//текстура карты
	map.loadFromFile("images/map.png");//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
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
			float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
			timer += time;
			clock.restart(); //перезагружает время
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
					if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(190, 1, 61, 61)); //если встретили символ пробел, то рисуем 1й квадратик
					if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(1, 1, 61, 61));//если встретили символ s, то рисуем 2й квадратик
					if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(126, 1, 61, 61));//если встретили символ 0, то рисуем 3й квадратик
					if ((TileMap[i][j] == '.')) s_map.setTextureRect(IntRect(55, 1, 61, 61));

					s_map.setPosition(j * 61, i * 61);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

					window.draw(s_map);//рисуем квадратики на экран
				}
			ostringstream ScoreStr, TimerS, TimerM;    // объявили переменную
			ScoreStr << p.Score;
			TimerS << timer / 1000000;
			TimerM << timer / 10000 % 100;
			text.setString("Score: " + ScoreStr.str() + "\n" + "Time: " + TimerS.str() + "." + TimerM.str());//задает строку тексту

			text.setPosition(1, 1);//задаем позицию текста, центр камеры
			window.draw(text);//рисую этот текст

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
			ostringstream ScoreStr, TimerS, TimerM;    // объявили переменную
			ScoreStr << p.Score;
			TimerS << timer / 1000000;
			TimerM << timer / 10000 % 100;
			text.setString("Game Over \n\nScore: " + ScoreStr.str() + "\n" + "Time: " + TimerS.str() + "." + TimerM.str());//задает строку тексту
			text.setPosition(500, 330);//задаем позицию текста, центр камеры
			window.draw(text);
			window.display();

		}
		if (end)
		{
			
			window.clear();
			ostringstream ScoreStr, TimerS, TimerM;    // объявили переменную
			ScoreStr << p.Score;
			TimerS << timer / 1000000;
			TimerM << timer / 10000 % 100;
			text.setString("YOU ARE WIN!!! \n\nScore: " + ScoreStr.str() + "\n" + "Time: " + TimerS.str() + "." + TimerM.str());//задает строку тексту
			text.setPosition(500, 330);//задаем позицию текста, центр камеры
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