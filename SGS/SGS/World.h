#pragma once
#include<vector>
#include"Particle.h"

class World
{
private:
    Particle **particles;
	int numberOfParticles;
    int area;
    int dimensions;
public:
    World(float area, int dimensions);
    void InitWorld(int numberOfParticles, float massBase);
    void AddParticle(Particle *p);
    void Step();
    Particle** GetParticles();
	int GetNumberOfParticles();
    void MergeParticles();
    void CalcVelocity();
    void ApplyVelocity();
    int GetDimensions();
    int GetArea();
    ~World();
};