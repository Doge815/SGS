#include "particle.h"

Particle::Particle()
{
}

void Particle::SetPosition(double px, double py, double vx, double vy, double mass)
{
	Particle::position = { new double[2]{px, py} };
	Particle::velocity = { new double[2]{vx, vy} };
	Particle::mass = mass;
}

Particle::~Particle()
{
    delete position;
    delete velocity;
}

double *Particle::GetPosition()
{
	return position;
}