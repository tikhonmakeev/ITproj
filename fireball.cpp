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
class createFireball :public Fire {
public:
	CircleShape *fb;
	createFireball(int x, int y) {
		fb = new CircleShape(x, y);
		fb.setPosition(x, y);
		fb.setRadius(radius);
		fb.setFillColor(Color(255,123,0));
		fb.setOrigin(radius, radius);
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
		Fireball f1(30, 30);
		window.draw(f1.fireball);
		window.clear();
		window.display();
	}
	return 0;
}
