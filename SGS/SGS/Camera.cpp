#include "Camera.h"
#include "World.h"
#include "Particle.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

Camera::Camera(sf::RenderWindow *window, World *world)
{
    Camera::window = window;
    Camera::world = world;
    Camera::shape = sf::CircleShape(2);
    shape.setFillColor(sf::Color::White);
    Zoom = 1;
}

void Camera::DrawImage()
{
    Particle **particles = world->GetParticles();
    Particle *biggest = nullptr;
    int alive = world->GetNumberOfParticles();
    for(int i = 0; i < world->GetNumberOfParticles(); i++)
    {
        if(particles[i] == nullptr) 
        {
            alive--;
            continue;
        }
        if(biggest == nullptr)
        {
            biggest = particles[i];
            continue;
        }
        if(particles[i]->GetMass() > biggest->GetMass())
        {
            biggest = particles[i];
        }
    }
    if(FixedZoom)
    {
        Particle *FarAway = nullptr;
        double dist;
        for(int i = 0; i < world->GetNumberOfParticles(); i++)
        {
            if(particles[i] == nullptr) 
            {
                continue;
            }
            double d = std::abs(particles[i]->GetPosition()[0] - biggest->GetPosition()[0]);
            double dd = std::abs(particles[i]->GetPosition()[1] - biggest->GetPosition()[1]);
            if(dd > d) d = dd;
            if(d > dist) dist = d;
        }
        Zoom = window->getSize().x  / dist / 2;
    }
    double OffsetX = - biggest->GetPosition()[0] * Zoom + window->getSize().x / 2 - biggest->GetRad();
    double OffsetY = - biggest->GetPosition()[1] * Zoom + window->getSize().y / 2 - biggest->GetRad();
    for (size_t i = 0; i < world->GetNumberOfParticles(); i++)
    {
        if(particles[i] == nullptr) continue;
		double* a = particles[i]->GetPosition();
		shape.setPosition(a[0]*Zoom + OffsetX, a[1]*Zoom + OffsetY);
        shape.setRadius(std::ceil(particles[i]->GetRad()));
		window->draw(shape);
	}

    sf::Text text;
    sf::Font f = sf::Font();
    if(!f.loadFromFile("./Arial.ttf"))
    {
        throw;
    }
    text.setFont(f);
    text.setColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setPosition(0,0);

    text.setString("Particles: " + std::to_string(alive));

    window->draw(text);
}

void Camera::ZoomIn()
{
    Zoom *= 1.25f;
}

void Camera::ZoomOut()
{
    Zoom /= 1.25f;
}

double Camera::GetZoom()
{
    return Zoom;
}

void Camera::SetFixedZoom(bool fixed)
{
    FixedZoom = fixed;
}
bool Camera::GetFixedZoom()
{
    return FixedZoom;
}