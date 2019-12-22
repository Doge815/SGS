#pragma once
#include"Particle.h"

class World
{
private:
    Particle **particles;
	int numberOfParticles;
    int dimensions;
public:
    #pragma region Con-/Destructor
    World(float area, int dimensions);
    ~World();
	#pragma endregion  Con-/Destructor
	
	#pragma region Gets&Sets
    int GetDimensions();
    int GetArea();
    Particle** GetParticles();
    int GetNumberOfParticles();
	#pragma  endregion  Gets&Sets

	#pragma region Calc
    void InitWorld(int numberOfParticles, float massBase, float area);
    void AddParticle(Particle* p);
    void Step();
    void MergeParticles();
    void CalcVelocity();
    void ApplyVelocity();
	#pragma endregion Calc
};