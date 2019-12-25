#pragma once
#include"Particle.h"
#include "Camera.h"

class World
{
private:
    Particle **particles;
	int numberOfParticles;
    int dimensions;
    Camera* cam;
public:
    #pragma region Con-/Destructor
    World(int dimensions);
    ~World();
	#pragma endregion  Con-/Destructor
	
	#pragma region Gets&Sets
    int GetDimensions();
    Particle** GetParticles();
    int GetNumberOfParticles();
    void SetCamera(Camera* c);
    Camera* GetCamera();
	#pragma  endregion  Gets&Sets

	#pragma region Calc
    void InitWorld(int numberOfParticles, float massBase, float area);
    void AddParticle(Particle* p);
    void Step();
    void MergeParticles();
    void CalcVelocity();
    void ApplyVelocity();
    void AddParticleFromUI(double x, double y);
	#pragma endregion Calc
};