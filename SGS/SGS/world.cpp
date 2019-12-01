#define _USE_MATH_DEFINES

#include "world.h"
#include "particle.h"
#include <math.h>

world::world(int numberOfParticles, float areaX, float areaY, float areaCoverage, float massFac, float massBase)
{
	world::numberOfParticles = numberOfParticles;
	world::particles = { new particle[numberOfParticles] };
    for (size_t i = 0; i < numberOfParticles; i++)
    {
		long theta	= (long)(rand() / RAND_MAX * M_PI * 2);
		long r		= (long)(rand() / RAND_MAX * areaX * areaCoverage);
		long m = (long)(massFac * rand() / RAND_MAX * M_PI + massBase);

		long px		= (long)(cos(theta * M_PI / 180) * r);
		long py		= (long)(sin(theta * M_PI / 180) * r);

		long vx		= py / 500;
		long vy		= -px / 500;
		world::particles[i].SetPosition(py, px, vx, vy, m);
    }
    
}

world::~world()
{
	delete[] world::particles;
}

void world::Step()
{
    for (size_t i = 0; i < world::numberOfParticles; i++)
    {
    }
}

int world::GetNumberOfParticles()
{
	return world::numberOfParticles;
}

particle* world::GetParticles()
{
	return world::particles;
}

long RandomFloat(long a, long b) {
	long random = ((long)rand()) / (long)RAND_MAX;
	long diff = b - a;
	long r = random * diff;
	return a + r;
}