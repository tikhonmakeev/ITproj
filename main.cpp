#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "magicka", Style::None);
	window.setFramerateLimit(60);
	int radius = 60;
	sf::CircleShape shape;
	shape.setPosition(450, 450);
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(radius,radius);
	int speed = 100;

	Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed or Keyboard::isKeyPressed(Keyboard::Key::F4))
				window.close();
		}

		float elapsed = clock.restart().asMilliseconds();

		if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
			shape.move(-speed * elapsed / 1000, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
			shape.move(speed * elapsed / 1000, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			shape.move(0,-speed * elapsed / 1000);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
			shape.move(0,speed * elapsed / 1000);
		}



		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}