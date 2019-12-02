#include <SFML/Graphics.hpp>
#include "world.h"
#include "particle.h"
const int dimensions = 2;

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SGS", sf::Style::Titlebar | sf::Style::Close);
	sf::CircleShape shape(2.f);
    shape.setFillColor(sf::Color::White);

	World* w = new World(10000, 500, 0.6f, 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		Particle *p = w->GetParticles();
		for (size_t i = 0; i < w->GetNumberOfParticles(); i++)
		{
			double* a = p[i].GetPosition();
			shape.setPosition(a[0], a[1]);
			window.draw(shape);
		}
        window.display();
    }

    return 0;
}