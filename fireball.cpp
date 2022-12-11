#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "vector2.hpp"
using namespace sf;
using namespace std;
class Fire {
public:
	void setBurning(string obj, int duration) {

	};
protected:
	int dmgpersec = 5;
};
class Fireball : public Fire {
public:
	Fireball(int x, int y) {
	        posX = x;
	        posY = y;
	};
	vector <CircleShape> fbs;
	CircleShape draw(int x, int y, vector <CircleShape> fbs){
		fbs.push_back(CircleShape(x, y));
		fbs[0].setPosition(x, y);
		fbs[0].setRadius(radius);
		fbs[0].setFillColor(Color(255,123,0));
		fbs[0].setRotation(0);
		fbs[0].setOrigin(radius, radius);
        return fbs[0];
	};
    int getPosX(){
        return posX;
    };
    int getPosY(){
        return posY;
    };
    int getSpeed(){
		return speed;
    };
    void setPosX(int value){
		posX = value;
	};
	void setPosY(int value){
		posY = value;
	};
private:
	int radius = 20;
	int speed = 100;
	float timeSpawned = 0;
	int posX;
	int posY;
	Vector2f _motion;
};
int main() {
	RenderWindow window(VideoMode(600, 600), "magicka", Style::None);
	//class RenderWindow &win = window;
	window.setFramerateLimit(60);
	Clock clock;
	Event event;
	int a = 0;
	vector <Fireball> fbsss;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Key::Escape))
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Space) and a == 0) {
			fbsss.push_back(Fireball(200, 200));
			fbsss[0].draw(fbsss[0].getPosX(), fbsss[0].getPosY(), fbsss[0].fbs);
			a = 1;
		};
		if (a == 1) {
			float elapsed = clock.restart().asMilliseconds();
			//√ƒе то используетс€ back на пустой вектор
			if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
				fbsss[0].fbs[0].move(fbsss[0].getSpeed() * elapsed / 1000 * cos(fbsss[0].fbs[0].getRotation()), fbsss[0].getSpeed() * elapsed / 1000 * sin(fbsss[0].fbs[0].getRotation()));
			};
			window.clear();

			window.draw(fbsss[0].fbs[0]);
			window.display();
		};
	};
	return 0;
}
