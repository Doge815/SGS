#include "Camera.h"
#include "World.h"
#include "Particle.h"
#include <math.h>
#include <SFML/Graphics.hpp>

Camera::Camera(sf::RenderWindow *window, World *world)
{
    Camera::window = window;
    Camera::world = world;
    Camera::shape = sf::CircleShape(2);
    shape.setFillColor(sf::Color::White);
}

void Camera::DrawImage()
{
    Particle **particles;
    Particle *Biggest = particles[0];
    for(int i = 0; i < world->GetNumberOfParticles(); i++)
    {
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