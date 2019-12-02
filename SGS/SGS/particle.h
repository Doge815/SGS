#pragma once
#include<vector>

class Particle
{
private:
    double *position;
    double *velocity;
	double mass;
public:
    Particle();
	void SetPosition(double px, double py, double vx, double vy, double mass);
	double *GetPosition();
    ~Particle();
};