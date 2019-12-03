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
	void SetPosition(double x, double y);
    void SetVelocity(double x, double y);
    void SetMass(double mass);

	double *GetPosition();
    double *GetVelocity();
    double GetMass();
    double GetRad();
    ~Particle();
};

