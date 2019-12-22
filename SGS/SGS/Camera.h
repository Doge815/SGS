#pragma once

#include <SFML/Graphics.hpp>
#include "World.h"

enum CameraTarget { Middle, CenterOfMass, High };
enum CameraType { Ortographic, D3, D4Flat, D4Color };

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
    #pragma region Con-/Destructor
    Camera(sf::RenderWindow* window, World* world);
	#pragma endregion Con-/Destructor

	#pragma region Gets&Sets
	void ZoomIn();
    void ZoomOut();
    void SetZoom(double zoom);
    double GetZoom();
    void SetFixedZoom(bool fixed);
    bool GetFixedZoom();
    void SetTarget(CameraTarget target);
    CameraTarget GetTarget();
	#pragma endregion Gets&Sets

	#pragma region Calc
    void DrawImage();
    double* WorldToScreen(double* p);
    double* ScreenToWorld(double* p);
	#pragma endregion Calc
};
