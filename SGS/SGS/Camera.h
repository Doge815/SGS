#pragma once

#include <SFML/Graphics.hpp>
#include "World.h"
#include "Particle.h"

enum CameraTarget { Middle, CenterOfMass, High };

class Camera
{
private:
    sf::RenderWindow *window;
    World *world;
    sf::CircleShape shape;
    double Zoom;
    double OffsetX;
    double OffsetY;
    bool FixedZoom;
    CameraTarget target = High;
    void CalcOffset();
public:
    Camera(sf::RenderWindow *window, World *world);
    void DrawImage();
    void ZoomIn();
    void ZoomOut();
    double GetZoom();
    void SetFixedZoom(bool fixed);
    bool GetFixedZoom();
    void SetTarget(CameraTarget target);
    CameraTarget GetTarget();
    sf::Vector2f WorldToScreen(sf::Vector2f p);
    sf::Vector2f WorldToScreen(double* p);
    double WorldToScreenX(double x);
    double WorldToScreenY(double y);
    sf::Vector2f ScreenToWorld(sf::Vector2f p);
    sf::Vector2f ScreenToWorld(double* p);
    double ScreenToWorldX(double x);
    double ScreenToWorldY(double y);

};
