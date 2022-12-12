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
	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{//çäåñü ðåàëèçîâàí âðàã, ìåíÿþùèé íàïðàâëåíèå ïîñëå êàñàíèÿ ñòåíû, íàì òàêîå íå î÷ ïîäõîäèò
				/*if (TileMap[i][j] == '0')//åñëè ýëåìåíò íàø òàéëèê çåìëè, òî
				{
					if (Dy > 0) { y = i * 32 - h; }//ïî Y âíèç=>èäåì â ïîë(ñòîèì íà ìåñòå) èëè ïàäàåì. Â ýòîò ìîìåíò íàäî âûòîëêíóòü ïåðñîíàæà è ïîñòàâèòü åãî íà çåìëþ, ïðè ýòîì ãîâîðèì ÷òî ìû íà çåìëå òåì ñàìûì ñíîâà ìîæåì ïðûãàòü
					if (Dy < 0) { y = i * 32 + 32; }//ñòîëêíîâåíèå ñ âåðõíèìè êðàÿìè êàðòû(ìîæåò è íå ïðèãîäèòüñÿ)
					if (Dx > 0) { x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }//ñ ïðàâûì êðàåì êàðòû
					if (Dx < 0) { x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }// ñ ëåâûì êðàåì êàðòû
				}
			}
		*/
			};
	};
	void update(float time)
	{
		if (name == "EasyEnemy") {//ñîçäàòü ëåãêîãî áîòà
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//ìåíÿåò íàïðàâëåíèå ïðèìåðíî êàæäûå 3 ñåê
			checkCollisionWithMap(dx, 0);
			x += dx * time;
			sprite.setPosition(x + w / 2, y + h / 2); //çàäàåì ïîçèöèþ ñïðàéòà â ìåñòî åãî öåíòðà
			if (health <= 0) { life = false; }
		}
	}
};
class Spell {
public:
	float dx, dy, x, y, speed= 10;
	int w, h;
	bool isBurning = false;
	string name;
	Texture texture;
	Sprite sprite;
	float PI = 3.14159265;
	//float angle = Mouse::getPosition(window);
	Spell(Image& image, float X, float Y, int W, int H, string Name, int mouseposX, int mouseposY) {
		x = X; y = Y; w = W; h = H; name = Name;
		dx = 0; dy = 0;
		int angle = (180.f / PI) * atan((mouseposY - y) / (mouseposX - x));
		std::cout << angle<<endl;
		if (name == "fireball") {
			int dmgpersec = 5;
			texture.loadFromImage(image);
			sprite.setPosition(x, y);
			sprite.setTexture(texture);
			sprite.setOrigin(w / 12, h / 2);
			sprite.scale(0.2f, 0.2f);
			sprite.setTextureRect(IntRect(0, 0, w/6, h));
			sprite.setRotation(angle);
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
		dx = speed * cos(sprite.getRotation());
		dy = speed * sin(sprite.getRotation());
		x += dx * time;
		y += dy * time;
		//checkCollisionWithMap(dx, 0);//îáðàáàòûâàåì ñòîëêíîâåíèå ïî Õ
		sprite.setPosition(x + w / 12, y + h / 2);
		//checkCollisionWithMap(0, dy);//îáðàáàòûâàåì ñòîëêíîâåíèå ïî Y
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
	int a = 0;
	Vector2i pixelPos = Mouse::getPosition(window);
	int mouseposX = window.mapPixelToCoords(pixelPos).x;
	int mouseposY = window.mapPixelToCoords(pixelPos).y;
	Spell fireball(fireballImage, 300, 300, 3072, 512, "fireball", mouseposX, mouseposY);
	while (window.isOpen())
	{
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Key::Escape))
				window.close();
		}
		if (event.type == Event::MouseButtonPressed and a== 0) {
			Vector2i pixelPos = Mouse::getPosition(window);
			int mouseposX = window.mapPixelToCoords(pixelPos).x;
			int mouseposY = window.mapPixelToCoords(pixelPos).y;
			float PI = 3.14159265;
			std::cout << ((180.f / PI) * atan((mouseposY - fireball.y) / (mouseposX - fireball.x)))<<endl;
			fireball.sprite.setRotation((180.f / PI) * atan((mouseposY - fireball.y) / (mouseposX - fireball.x)));
			a = 1;
		}
		if (a == 1) {
			//fireball.update(time);

			window.clear();

			window.draw(fireball.sprite);
			window.display();
		}
	};
	return 0;
};
