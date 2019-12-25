#pragma once

class Particle
{
private:
    int dimensions;
    double* position;
    double* velocity;
	double mass;
    
public:
	#pragma region Con-/Destructor
    Particle(int dimensions);
	~Particle();
	#pragma endregion Con-/Destructor

	#pragma region Gets&Sets
    void SetPosition(double* p);
    void SetVelocity(double* v);
    void SetMass(double mass);

    double* GetPosition();
    double* GetVelocity();
    double GetMass();
    double GetRad();
	#pragma endregion Gets&Sets
};
