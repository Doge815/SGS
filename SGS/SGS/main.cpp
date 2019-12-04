#include <SFML/Graphics.hpp>
#include "World.h"
#include "Particle.h"
#include <iostream>
#include <math.h>
#include "Camera.h"

int main()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(500, 500), "SGS", sf::Style::Titlebar | sf::Style::Close);
	World *world = new World(200, 500, 10);
    Camera *camera = new Camera(window, world); 
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        world->Step();
        window->clear();
		camera->DrawImage();
        window->display();
    }

    return 0;
}
//g++ Particle.h World.h Camera.h && g++ -c main.cpp Particle.cpp World.cpp Camera.cpp && g++ main.o World.o Particle.o Camera.o -o SGS -lsfml-graphics -lsfml-window -lsfml-system && ./SGS