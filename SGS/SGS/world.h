#pragma once
#include<vector>
#include"particle.h"

class World
{
private:
    Particle *particles;
	int numberOfParticles;
public:
    World(int numberOfParticles, float areaX, float massFac, float massBase);
    void Step();
    Particle* GetParticles();
	int GetNumberOfParticles();
    ~World();
};