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
    double Zoom;
    bool FixedZoom;
public:
    Camera(sf::RenderWindow *window, World *world);
    void DrawImage();
    void ZoomIn();
    void ZoomOut();
    double GetZoom();
    void SetFixedZoom(bool fixed);
    bool GetFixedZoom();
};
