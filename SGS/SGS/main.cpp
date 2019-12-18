#include <SFML/Graphics.hpp>
#include "World.h"
#include "Particle.h"
#include <iostream>
#include <string>
#include <math.h>
#include "Camera.h"

const int size = 500;
const int dimensions = 2;

int main()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(size, size), "SGS", sf::Style::Titlebar | sf::Style::Close);
	World *world = new World(size, dimensions);
    #if true
    world->InitWorld(200, 10);
    #else
    Particle *base = new Particle();
    base->SetVelocity(0,0);
    base->SetPosition(0, 0);
    base->SetMass(100);
    world->AddParticle(base);
    #endif
    std::cout << "a" << std::endl;
    Camera *camera = new Camera(window, world); 
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                camera->ZoomIn();
                std::cout << std::to_string(camera->GetZoom()) << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                camera->ZoomOut();
            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                //Todo: Code should be in World, not working if zoom != 1
                Particle *b = new Particle(dimensions);
                std::cout << event.mouseButton.x - size/2<< ", " << event.mouseButton.x - size/2<< std::endl;
                double* pos = {new double[dimensions]};
                pos[0] = event.mouseButton.x - size/2;
                pos[1] = event.mouseButton.y - size/2;
                b->SetPosition(pos);
                b->SetVelocity({new double[dimensions]});
                //b->SetVelocity(event.mouseButton.y - size/10000, event.mouseButton.x - size/10000);
                b->SetMass(100);
                world->AddParticle(b);
            }
        }

        world->Step();
        window->clear();
		camera->DrawImage();
        window->display();
    }

    return 0;
}
//g++ Particle.h World.h Camera.h && g++ -c main.cpp Particle.cpp World.cpp Camera.cpp && g++ main.o World.o Particle.o Camera.o -o SGS -lsfml-graphics -lsfml-window -lsfml-system && ./SGS