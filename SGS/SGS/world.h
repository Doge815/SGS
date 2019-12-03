#pragma once
#include<vector>
#include"particle.h"

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
    ~World();
};