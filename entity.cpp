#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Entity {
public:
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
	enum { left, right, up, down, stay } state;//состояния объекта

	Player(Image& image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "вставить имя") {
			//sprite.setTextureRect(IntRect(, w, h));добавить текстуру
		}
	}

	void control() {
		if (Keyboard::isKeyPressed) {//класс проверки нажатия клавиш управления
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

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		/**for ()//проходимся по элементам карты
			for ()
			{
				if (Map[i][j] == '1')
				{
					if (Dy > 0) {}//по Y вниз=>идем в пол(стоим на месте).
					if (Dy < 0) {}//столкновение с верхними краями карты
					if (Dx > 0) {}//с правым краем карты
					if (Dx < 0) {}// с левым краем карты
				}
			}
	*/
	};
	void update(float time)
	{
		control();//функция управления персонажем
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right:dx = speed; break;//состояние идти вправо
		case left:dx = -speed; break;//состояние идти влево
		case up: dy = speed; break;
		case down: dy = -speed; break;
		case stay: break;		
		}
		x += dx * time;
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy * time;
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		//if (life) { setPlayerCoordinateForView(x, y); } можно добавить, чтоб камера не всегда была над персонажем
	}
};
class Enemy :public Entity {
public:
	Enemy(Image& image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;//пусть этот монстр всегда двигается
		}
	}
	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{//здесь реализован враг, меняющий направление после касания стены, нам такое не оч подходит
				/*if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
				{
					if (Dy > 0) { y = i * 32 - h; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
					if (Dy < 0) { y = i * 32 + 32; }//столкновение с верхними краями карты(может и не пригодиться)
					if (Dx > 0) { x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }//с правым краем карты
					if (Dx < 0) { x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }// с левым краем карты
				}
			}
		*/
			};
	};
	void update(float time)
	{
		if (name == "EasyEnemy") {//создать легкого бота
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
			checkCollisionWithMap(dx, 0);
			x += dx * time;
			sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
			if (health <= 0) { life = false; }
		}
	}
};
class Spell {
public:
	float dx, dy, x, y, speed= 20;
	int w, h;
	bool isBurning = false;
	string name;
	Texture texture;
	Sprite sprite;
	//float angle = Mouse::getPosition(window);
	Spell(Image& image, float X, float Y, int W, int H, string Name, int mouseposX, int mouseposY) {
		x = X; y = Y; w = W; h = H; name = Name;
		dx = 0; dy = 0;
		int angle = atan((mouseposY - y) / (mouseposX - x));
		if (name == "fireball") {
			int dmgpersec = 5;
			texture.loadFromImage(image);
			sprite.setPosition(x, y);
			sprite.setTexture(texture);
			sprite.setOrigin(w / 2, h / 2);
			sprite.setTextureRect(IntRect(0,0, w/6, h));
			sprite.setRotation(angle);
		}
	}
	void setBurning(string obj, int duration, float time) {
		isBurning = true;
		float burnTimer = time;
		if (time - burnTimer > duration) { isBurning = false; }
	};
	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		/**for ()//проходимся по элементам карты
			for ()
			{
				if (Map[i][j] == '1')
				{
					if (Dy > 0) {}//по Y вниз=>идем в пол(стоим на месте).
					if (Dy < 0) {}//столкновение с верхними краями карты
					if (Dx > 0) {}//с правым краем карты
					if (Dx < 0) {}// с левым краем карты
				}
			}
	*/
	};
	void update(float time)
	{
		dx = speed * cos(sprite.getRotation());
		dy = speed * sin(sprite.getRotation());
		x += dx * time;
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy * time;
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
	}
};
int main() {
	Image fireballImage;
	fireballImage.loadFromFile("FireTexture.png");
	RenderWindow window(VideoMode(600, 600), "magicka", Style::None);
	//class RenderWindow &win = window;
	window.setFramerateLimit(60);
	Clock clock;
	Event event;
	
	
	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		int mouseposX = window.mapPixelToCoords(pixelPos).x;
		int mouseposY = window.mapPixelToCoords(pixelPos).y;
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Key::Escape))
				window.close();
		}
		
		Spell fireball(fireballImage, 40, 40, 3072, 512, "fireball", mouseposX, mouseposY);
		window.clear();

		window.draw(fireball.sprite);
		window.display();
	};
	return 0;
};