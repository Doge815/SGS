#pragma once
#include<vector>
#include"particle.h"

class world
{
private:
    particle *particles;
	int numberOfParticles;
public:
    world(int numberOfParticles, float areaX, float areaY, float areaCoverage, float massFac, float massBase);
    void Step();
    particle* GetParticles();
	int GetNumberOfParticles();
    ~world();
};