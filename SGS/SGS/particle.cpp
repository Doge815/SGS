#include "particle.h"

Particle::Particle()
{
}

void Particle::SetPosition(double x, double y)
{
	Particle::position = { new double[2]{x, y} };
}

void Particle::SetVelocity(double x, double y)
{
	Particle::velocity = { new double[2]{x, y} };
}

void Particle::SetMass(double mass)
{
	Particle::mass = mass;
}

double* Particle::GetPosition()
{
	return Particle::position;
}

double* Particle::GetVelocity()
{
	return Particle::velocity;
}

double Particle::GetMass()
{
	return Particle::mass;
}

Particle::~Particle()
{
    delete position;
    delete velocity;
}