#include "Camera.h"
#include "World.h"
#include "Particle.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include <iostream>

Camera::Camera(sf::RenderWindow *window, World *world)
{
    Camera::window = window;
    Camera::world = world;
    Camera::shape = sf::CircleShape(2);
    shape.setFillColor(sf::Color::White);
}

void Camera::DrawImage()
{
    Particle **particles = world->GetParticles();
    Particle *Biggest = nullptr;
    for(int i = 0; i < world->GetNumberOfParticles(); i++)
    {
        if(particles[i] == nullptr) continue;
        if(Biggest == nullptr)
        {
            Biggest = particles[i];
            continue;
        }
        if(particles[i]->GetMass() > Biggest->GetMass())
        {
            Biggest = particles[i];
        }
    }
    double OffsetX = - Biggest->GetPosition()[0] + window->getSize().x / 2;
    double OffsetY = - Biggest->GetPosition()[1] + window->getSize().y / 2;
    for (size_t i = 0; i < world->GetNumberOfParticles(); i++)
		{
            if(particles[i] == nullptr) continue;
			double* a = particles[i]->GetPosition();
			shape.setPosition(a[0] + OffsetX, a[1] + OffsetY);
            shape.setRadius(std::ceil(particles[i]->GetRad()));
			window->draw(shape);
		}
}