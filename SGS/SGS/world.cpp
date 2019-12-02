#define _USE_MATH_DEFINES

#include "world.h"
#include "particle.h"
#include <math.h>
#include <iostream>
#include<time.h>

double RandomFloat(double a, double b);

World::World(int numberOfParticles, float areaX, float massFac, float massBase)
{
	srand(time(NULL));
	World::numberOfParticles = numberOfParticles;
	World::particles = { new Particle[numberOfParticles] };
    for (size_t i = 0; i < numberOfParticles; i++)
    {
		double theta	= ((double)rand() / (RAND_MAX)* 360);
		double r		= ((double)rand() / (RAND_MAX)* areaX / 2);
		double m		= ((double)rand() / (RAND_MAX)* M_PI + massBase);

		double px = cos(theta * M_PI / 180) * r + areaX / 2;
		double py = sin(theta * M_PI / 180) * r + areaX / 2;

		double vx = py / 500;
		double vy = -px / 500;
		World::particles[i].SetPosition(px, py, vx, vy, m);
	}
}

World::~World()
{
	delete[] World::particles;
}

void World::Step()
{
    for (size_t i = 0; i < World::numberOfParticles; i++)
    {
    }
}

int World::GetNumberOfParticles()
{
	return World::numberOfParticles;
}

Particle* World::GetParticles()
{
	return World::particles;
}

double RandomFloat(double a, double b) {
	double random = ((double)rand()) / (double)RAND_MAX;
	double diff = b - a;
	double r = random * diff;
	return a + r;
}