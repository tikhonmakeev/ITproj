#include "map.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>
using namespace sf;
using namespace std;
class Entity {
	public:
		Event event;
		float dx, dy, x, y, speed, moveTimer;
		int w, h, health;
		bool life, isMove, isBurning;
		Texture texture;
		Sprite sprite;
		string name;
		Entity(Image& image, float X, float Y, int W, int H, string Name) {
			x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
			speed = 0; health = 100; dx = 0; dy = 0;
			life = true; isMove = false, isBurning = false;
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setOrigin(w / 2, h / 2);
		}
};
class Player :public Entity {
public:
	bool isShoot;
	enum { left, right, up, down, stay } state;//ñîñòîÿíèÿ îáúåêòà

	Player(Image& image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "âñòàâèòü èìÿ") {
			//sprite.setTextureRect(IntRect(, w, h));äîáàâèòü òåêñòóðó
		}
	}

	void control() {
		if (Keyboard::isKeyPressed) {//êëàññ ïðîâåðêè íàæàòèÿ êëàâèø óïðàâëåíèÿ
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				state = left; speed = speed;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right; speed = speed;
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				state = up; speed = speed;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down; speed = speed;
			}
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ô öèÿ ïðîâåðêè ñòîëêíîâåíèé ñ êàðòîé
	{
		/**for ()//ïðîõîäèìñÿ ïî ýëåìåíòàì êàðòû
			for ()
			{
				if (Map[i][j] == '1')
				{
					if (Dy > 0) {}//ïî Y âíèç=>èäåì â ïîë(ñòîèì íà ìåñòå).
					if (Dy < 0) {}//ñòîëêíîâåíèå ñ âåðõíèìè êðàÿìè êàðòû
					if (Dx > 0) {}//ñ ïðàâûì êðàåì êàðòû
					if (Dx < 0) {}// ñ ëåâûì êðàåì êàðòû
				}
			}
	*/
	};
	void update(float time)
	{
		control();//ôóíêöèÿ óïðàâëåíèÿ ïåðñîíàæåì
		switch (state)//òóò äåëàþòñÿ ðàçëè÷íûå äåéñòâèÿ â çàâèñèìîñòè îò ñîñòîÿíèÿ
		{
		case right:dx = speed; break;//ñîñòîÿíèå èäòè âïðàâî
		case left:dx = -speed; break;//ñîñòîÿíèå èäòè âëåâî
		case up: dy = speed; break;
		case down: dy = -speed; break;
		case stay: break;		
		}
		x += dx * time;
		checkCollisionWithMap(dx, 0);//îáðàáàòûâàåì ñòîëêíîâåíèå ïî Õ
		y += dy * time;
		checkCollisionWithMap(0, dy);//îáðàáàòûâàåì ñòîëêíîâåíèå ïî Y
		sprite.setPosition(x + w / 2, y + h / 2); //çàäàåì ïîçèöèþ ñïðàéòà â ìåñòî åãî öåíòðà
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		//if (life) { setPlayerCoordinateForView(x, y); } ìîæíî äîáàâèòü, ÷òîá êàìåðà íå âñåãäà áûëà íàä ïåðñîíàæåì
	}
};
class Enemy :public Entity {
public:
	Enemy(Image& image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;//ïóñòü ýòîò ìîíñòð âñåãäà äâèãàåòñÿ
		}
	}
	/*void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 64; i < (y + h) / 64; i++)
			for (int j = x / 64; j < (x + w) / 64; j++)
			{//çäåñü ðåàëèçîâàí âðàã, ìåíÿþùèé íàïðàâëåíèå ïîñëå êàñàíèÿ ñòåíû, íàì òàêîå íå î÷ ïîäõîäèò
				/*if (TileMap[i][j] == '0')//åñëè ýëåìåíò íàø òàéëèê çåìëè, òî
				{
					if (Dy > 0) { y = i * 64 - h; }//ïî Y âíèç=>èäåì â ïîë(ñòîèì íà ìåñòå) èëè ïàäàåì. Â ýòîò ìîìåíò íàäî âûòîëêíóòü ïåðñîíàæà è ïîñòàâèòü åãî íà çåìëþ, ïðè ýòîì ãîâîðèì ÷òî ìû íà çåìëå òåì ñàìûì ñíîâà ìîæåì ïðûãàòü
					if (Dy < 0) { y = i * 64 + 64; }//ñòîëêíîâåíèå ñ âåðõíèìè êðàÿìè êàðòû(ìîæåò è íå ïðèãîäèòüñÿ)
					if (Dx > 0) { x = j * 64 - w; dx = -0.1; sprite.scale(-1, 1); }//ñ ïðàâûì êðàåì êàðòû
					if (Dx < 0) { x = j * 64 + 64; dx = 0.1; sprite.scale(-1, 1); }// ñ ëåâûì êðàåì êàðòû
				}
			}
		}
	};*/
	void update(float time)
	{
		if (name == "EasyEnemy") {//ñîçäàòü ëåãêîãî áîòà
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//ìåíÿåò íàïðàâëåíèå ïðèìåðíî êàæäûå 3 ñåê
			//checkCollisionWithMap(dx, 0);
			x += dx * time;
			sprite.setPosition(x + w / 2, y + h / 2); //çàäàåì ïîçèöèþ ñïðàéòà â ìåñòî åãî öåíòðà
			if (health <= 0) { life = false; }
		}
	}
};
class Spell {
public:
	float dx, dy, x, y, speed= 1;
	int w, h;
	bool isBurning = false, toDelete = false;
	string name;
	Texture texture;
	Sprite sprite;
	float PI = 3.14159265;
	int angle;
	Spell(Image& image, float X, float Y, int W, int H, string Name, int mouseposX, int mouseposY) {
		x = X; y = Y; w = W; h = H; name = Name;
		dx = 0; dy = 0;
		angle = (180.f / PI) * atan((mouseposY - y) / (mouseposX - x));
		if (mouseposY < y) {
			angle = -angle;
		}
		std::cout << angle<<endl;
		if (name == "fireball") {
			int dmgpersec = 5;
			texture.loadFromImage(image);
			sprite.setPosition(x, y);
			sprite.setTexture(texture);
			sprite.setOrigin(w /3, h/2);
			sprite.scale(0.03f, 0.03f);
			sprite.setRotation(angle + 180.f);
		}
	}
	void setBurning(string obj, int duration, float time) {
		isBurning = true;
		float burnTimer = time;
		if (time - burnTimer > duration) { isBurning = false; }
	};
	void checkCollisionWithMap(float Dx, float Dy)//ô öèÿ ïðîâåðêè ñòîëêíîâåíèé ñ êàðòîé
	{
		/**for ()//ïðîõîäèìñÿ ïî ýëåìåíòàì êàðòû
			for ()
			{
				if (Map[i][j] == '1')
				{
					if (Dy > 0) {}//ïî Y âíèç=>èäåì â ïîë(ñòîèì íà ìåñòå).
					if (Dy < 0) {}//ñòîëêíîâåíèå ñ âåðõíèìè êðàÿìè êàðòû
					if (Dx > 0) {}//ñ ïðàâûì êðàåì êàðòû
					if (Dx < 0) {}// ñ ëåâûì êðàåì êàðòû
				}
			}
	*/
	};
	void update(float time)
	{
		if (angle > 0) {
			dx = speed * cos(sprite.getRotation() / 57.2958);
			dy = speed * sin(sprite.getRotation() / 57.2958);

		}
		else {
			dx = -1 * speed * cos(sprite.getRotation() / 57.2958);
			dy = -1 * speed * sin(sprite.getRotation() / 57.2958);
		}
		x += dx * time;
		y += dy * time;
		//sprite.setRotation((180.f / PI) * atan((mouseposY - fireball.y) / (mouseposX - fireball.x)));
		//checkCollisionWithMap(dx, 0);//îáðàáàòûâàåì ñòîëêíîâåíèå ïî Õ
		sprite.setPosition(x, y);
		//checkCollisionWithMap(0, dy);//îáðàáàòûâàåì ñòîëêíîâåíèå ïî Y
	}
	/*void interactionWithMap()//ф-ция взаимодействия с картой
	{
		for (int i = y / 64; i < (y + h) / 64; i++)//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 64; j < (x + w) / 64; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					toDelete = true;
				}

				if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
					x = 300; y = 300;//какое то действие... например телепортация героя
					TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
				}
			}
	}*/
};
int main() {
	int HEIGHT = 800;
	int WIDTH = 1280;
	Image wizard;
	wizard.loadFromFile("wizard.png");
	wizard.createMaskFromColor(Color(0, 0, 0));
	Texture herotexture;
	herotexture.loadFromImage(wizard);
	int playerW = 84; int playerH = 160;
	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 90, 160));//первый спрайт
	herosprite.setPosition(WIDTH/2-playerW/2, HEIGHT/2-playerH/2); //выводим спрайт в позицию x y 
	herosprite.setOrigin(playerW / 2, playerH / 2);

	Image fireballImage;
	fireballImage.loadFromFile("ballfire.png");
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "magicka", Style::None);
	//class RenderWindow &win = window;
	window.setFramerateLimit(60);
	Clock clock;
	Event event;
	int a = 0; float CurrentFrame = 0;//хранит текущий кадр
	list<Entity*> entities;
	list<Entity*>::iterator it;
	list<Entity*>::iterator it2;
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("map2bg.jpg");//загружаем файл для карты
	//map_image.createMaskFromColor(Color(0, 0, 0));не работает
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
	Vector2i pixelPos = Mouse::getPosition(window);
	int mouseposX = window.mapPixelToCoords(pixelPos).x;
	int mouseposY = window.mapPixelToCoords(pixelPos).y;
	Spell fireball(fireballImage, 500, 500, 3206, 1054, "fireball", mouseposX, mouseposY);
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart();
		time = time / 16000;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Key::Escape))
				window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left) {
				cout << "!!!!!";
			}
		}
		if (event.type == Event::MouseButtonPressed and a == 0) {
			Vector2i pixelPos = Mouse::getPosition(window);
			int mouseposX = window.mapPixelToCoords(pixelPos).x;
			int mouseposY = window.mapPixelToCoords(pixelPos).y;
			float PI = 3.14159265;


			a = 1;
		}
		if (a == 1) {
			fireball.update(time);
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) { herosprite.move(-0.6 * time, 0); herosprite.setTextureRect(IntRect(playerW, 192 - 20, -playerW, 158));
				/*CurrentFrame += 0.05 * time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
				if (CurrentFrame > 5) CurrentFrame -= 5; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
				herosprite.setTextureRect(IntRect(playerW * int(CurrentFrame), 172, playerW, 158)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
				herosprite.move(-0.5 * time, 0);//происходит само движение персонажа влево} //-0,1 это скорость, умножаем её на наше время и получаем пройденное расстояние*/
			}
			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) { /*herosprite.move(0.5 * time, 0); herosprite.setTextureRect(IntRect(0, 192 - 20, 95, 158));*/
			CurrentFrame += 0.07 * time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 5) CurrentFrame -= 5; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(10+playerW * int(CurrentFrame), 172, playerW, 158)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(0.6 * time, 0);//происходит само движение персонажа влево} //-0,1 это скорость, умножаем её на наше время и получаем пройденное расстояние
			} // см коммент выше
			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) { herosprite.move(0, -0.6 * time); herosprite.setTextureRect(IntRect(0, 0, 96 - 6, 192 - 32)); }// см выше
			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { herosprite.move(0, 0.6 * time); herosprite.setTextureRect(IntRect(0, 0, 96-6, 192-32)); }// см выше


			window.clear();
			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 64, 64)); //если встретили символ пробел, то рисуем 1й квадратик
					if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(448, 64, 512, 128));//bricks
					if ((TileMap[i][j] == 'x')) s_map.setTextureRect(IntRect(448, 192, 512, 256));//brownstone
					if ((TileMap[i][j] == 't')) s_map.setTextureRect(IntRect(192, 0, 256, 64));//top
					if ((TileMap[i][j] == 'T')) s_map.setTextureRect(IntRect(64, 0, 128, 64));//Left-top
					if ((TileMap[i][j] == 'b')) s_map.setTextureRect(IntRect(0, 448, 64, 512));//bot
					if ((TileMap[i][j] == 'l')) s_map.setTextureRect(IntRect(64, 64, 128, 128));//left
					if ((TileMap[i][j] == 'L')) s_map.setTextureRect(IntRect(0, 64, 64, 128));//Left-bot


					s_map.setPosition(j * 64, i * 64);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

					window.draw(s_map);//рисуем квадратики на экран
				}
			window.draw(fireball.sprite);
			window.draw(herosprite);
			window.display();
		}
	};
	return 0;
};