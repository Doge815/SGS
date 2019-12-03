#pragma once

#include <SFML/Graphics.hpp>
#include "World.h"
#include "Particle.h"

class Camera
{
private:
    sf::RenderWindow *window;
    World *world;
    sf::CircleShape shape;
public:
    Camera(sf::RenderWindow *window, World *world);
    void DrawImage();
};
