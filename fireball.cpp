#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
//#include "vector2.hpp"
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
        CircleShape draw(int x, int y){
                CircleShape fb(x, y);
				fb.setPosition(x, y);
				fb.setRadius(radius);
				fb.setFillColor(Color(255,123,0));
				fb.setOrigin(radius, radius);
                return fb;
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
        int setPosX(int value){
		posX += value;
	};
	int setPosY(int value){
		posY += value;
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
	RenderWindow window(sf::VideoMode(600, 600), "magicka", Style::None);
	//class RenderWindow &win = window;
	window.setFramerateLimit(60);
	Clock clock;
	while (window.isOpen())
	{
		Event event;
		Fireball f1(200, 200);
		CircleShape f=f1.draw(f1.getPosX(), f1.getPosY());
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed or Keyboard::isKeyPressed(Keyboard::Key::F4))
				window.close();
		}
		float elapsed = clock.restart().asMilliseconds();

		if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
			f.move(-(f1.getSpeed()) * elapsed / 1000, 0);
			f1.setPosX(-(f1.getSpeed()) * elapsed / 1000);
		};
		if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
			f.move(f1.getSpeed() * elapsed / 1000, 0);
			f1.setPosX(f1.getSpeed() * elapsed / 1000);
		};
		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			f.move(0,-(f1.getSpeed()) * elapsed / 1000);
			f1.setPosY(-(f1.getSpeed()) * elapsed / 1000);
		};
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
			f.move(0,f1.getSpeed() * elapsed / 1000);
			f1.setPosY(f1.getSpeed() * elapsed / 1000);
		};
		window.clear();

		window.draw(f);
		window.display();
	}
	return 0;
}
