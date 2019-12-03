#pragma once
#include<vector>
#include"Particle.h"

class World
{
private:
    Particle **particles;
	int numberOfParticles;
public:
    World(int numberOfParticles, float area, float massBase);
    void Step();
    Particle** GetParticles();
	int GetNumberOfParticles();
    void MergeParticles();
    void CalcVelocity();
    void ApplyVelocity();
    ~World();
};