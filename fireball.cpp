#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Fire {
public:
	void setBurning(string obj, int duration) {

	};
protected:
	int dmgpersec = 5;
};
class Fireball :public Fire {
public:
	Fireball(int x, int y) {
	        int posX = x;
                int posY = y;	
	};
        CircleShape draw(int x, int y){
                fb = CircleShape(x, y);
		fb.setPosition(x, y);
		fb.setRadius(radius);
		fb.setFillColor(Color(255,123,0));
		fb.setOrigin(radius, radius);
                return fb;
        };
        CircleShape draw(){
                fb = CircleShape(Fireball.x, Fireball.y);
		fb.setPosition(Fireball.x, Fireball.y);
		fb.setRadius(Fireball.radius);
		fb.setFillColor(Color(255,123,0));
		fb.setOrigin(Fireball.radius, Fireball.radius);
                return fb;
        };
private:
	int radius = 30;
	int speed = 100;
};
int main() {
	RenderWindow window(sf::VideoMode(900, 900), "magicka", Style::None);
	class RenderWindow &win = window;
	window.setFramerateLimit(60);
	Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed or Keyboard::isKeyPressed(Keyboard::Key::F4))
				window.close();
		}
		window.clear();


		Fireball f1(30, 30);
		window.draw(f1.draw(f1.posX,f1.posY));
		window.display();
	}
	return 0;
}
