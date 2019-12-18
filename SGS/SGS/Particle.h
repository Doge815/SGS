#pragma once
#include<vector>

class Particle
{
private:
    int dimensions;
    double* position;
    double* velocity;
	double mass;
    
public:
    Particle(int dimensions);
	void SetPosition(double* p);
    void SetVelocity(double* v);
    void SetMass(double mass);

	double *GetPosition();
    double *GetVelocity();
    double GetMass();
    double GetRad();
    ~Particle();
};

