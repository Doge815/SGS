#include "particle.h"

particle::particle()
{
}

void particle::SetPosition(long px, long py, long vx, long vy, long mass)
{
	particle::position = { new long[2]{px, py} };
	particle::velocity = { new long[2]{vx, vy} };
	particle::mass = mass;
}

particle::~particle()
{
    delete position;
    delete velocity;
}

long *particle::GetPosition()
{
	return position;
}