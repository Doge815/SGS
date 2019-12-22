#include "Camera.h"
#include "World.h"
#include "Particle.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#pragma region Con-/Destructor
Camera::Camera(sf::RenderWindow* window, World* world)
{
    Camera::window = window;
    Camera::world = world;
    Camera::shape = sf::CircleShape(2);
    shape.setFillColor(sf::Color::White);
    Zoom = 1;
    FixedZoom = false;
    Offset = { new double[world->GetDimensions()] };
}
#pragma endregion Con-/Destructor

#pragma region Gets&Sets
inline void Camera::ZoomIn()
{
    Zoom *= 1.25f;
}

inline void Camera::ZoomOut()
{
    Zoom /= 1.25f;
}

inline void Camera::SetZoom(double zoom)
{
    Camera::Zoom = zoom;
}

inline double Camera::GetZoom()
{
    return Zoom;
}

inline void Camera::SetFixedZoom(bool fixed)
{
    FixedZoom = fixed;
}

inline bool Camera::GetFixedZoom()
{
    return FixedZoom;
}

inline void Camera::SetTarget(CameraTarget target)
{
    Camera::target = target;
}

inline CameraTarget Camera::GetTarget()
{
    return target;
}
#pragma endregion Gets&Sets

#pragma region Calc
void Camera::DrawImage()
{
    Particle** particles = world->GetParticles();
    int alive = world->GetNumberOfParticles();
    for (int i = 0; i < world->GetNumberOfParticles(); i++)
    {
        if (particles[i] == nullptr)
        {
            alive--;
        }
    }
    if (alive == 0) return;
    CalcOffset();
    for (size_t i = 0; i < world->GetNumberOfParticles(); i++)
    {
        if (particles[i] == nullptr) continue;
        double* a = particles[i]->GetPosition();
        shape.setPosition(a[0] * Zoom + Offset[0], a[1] * Zoom + Offset[1]);
        shape.setRadius(std::ceil(particles[i]->GetRad() * Zoom));
        window->draw(shape);
    }

    sf::Text text;
    sf::Font f = sf::Font();
    if (!f.loadFromFile("./Arial.ttf"))
    {
        throw;
    }
    text.setFont(f);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setPosition(5, 5);

    text.setString("Particles: " + std::to_string(alive) + "\nZoom: " + std::to_string(Zoom));

    window->draw(text);
}

void Camera::CalcOffset()
{
    Particle** particles = world->GetParticles();
    switch (Camera::target)
    {
    case High:
    {
        Particle* biggest = nullptr;
        for (int i = 0; i < world->GetNumberOfParticles(); i++)
        {
            if (particles[i] == nullptr)
            {
                continue;
            }
            if (biggest == nullptr)
            {
                biggest = particles[i];
                continue;
            }
            if (particles[i]->GetMass() > biggest->GetMass())
            {
                biggest = particles[i];
            }
        }
        if (FixedZoom)
        {
            Particle* FarAway = nullptr;
            double dist = 0;
            for (int i = 0; i < world->GetNumberOfParticles(); i++)
            {
                if (particles[i] == nullptr) continue;
                //TODO: all dims!!!
                double d = std::abs(particles[i]->GetPosition()[0] - biggest->GetPosition()[0]);
                double dd = std::abs(particles[i]->GetPosition()[1] - biggest->GetPosition()[1]);
                if (dd > d) d = dd;
                if (d > dist) dist = d;
            }
            Zoom = world->GetArea() / dist / 2.5f;
        }
        for (size_t i = 0; i < world->GetDimensions(); i++)
        {
            Offset[i] = -biggest->GetPosition()[i] * Zoom + world->GetArea() / 2 - biggest->GetRad() * Zoom;
        }
    }
    break;
    case Middle:
    {
        Particle*** borders = { new Particle * *[world->GetDimensions()] };
        for (size_t i = 0; i < world->GetDimensions(); i++)
        {
            borders[i] = { new Particle * [2]{nullptr, nullptr} };
            for (size_t u = 0; i < world->GetNumberOfParticles(); i++)
            {
                if (borders[i][0] == nullptr ||
                    particles[u]->GetPosition()[i] - particles[u]->GetRad() <
                    borders[i][0]->GetPosition()[i] - borders[i][0]->GetRad())
                {
                    borders[i][0] = particles[u];
                }
                if (borders[i][1] == nullptr ||
                    particles[u]->GetPosition()[i] * particles[u]->GetRad() >
                    borders[i][1]->GetPosition()[i] + borders[i][1]->GetRad())
                {
                    borders[i][1] = particles[u];
                }
            }

        }
    }
    break;

    default:
        break;
    }

}

double* Camera::WorldToScreen(double* p)
{
    double* r = { new double[world->GetDimensions()] };
    try
    {
        for (size_t i = 0; i < world->GetDimensions(); i++)
        {
            r[i] = p[i] * Zoom + Offset[i];
        }
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << '\n';
    }
    return r;

}

double* Camera::ScreenToWorld(double* p)
{
    double* r = { new double[world->GetDimensions()] };
    try
    {
        for (size_t i = 0; i < world->GetDimensions(); i++)
        {
            r[i] = (p[i] - Offset[i]) / Zoom;
        }
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << '\n';
    }
    return r;
}
#pragma endregion Calc