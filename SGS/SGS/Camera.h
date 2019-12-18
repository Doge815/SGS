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
    double *Offset;
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
    double* WorldToScreen(double* p);
    double* ScreenToWorld(double* p);

};
