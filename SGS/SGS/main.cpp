#include <SFML/Graphics.hpp>
#include "world.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	world* w = new world(100, 150, 150, 0.8f, 0.6f, 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
		for (size_t i = 0; i < w->GetNumberOfParticles(); i++)
		{

		}
        window.display();
    }

    return 0;
}