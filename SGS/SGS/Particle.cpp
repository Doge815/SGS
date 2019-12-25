#define _USE_MATH_DEFINES

#include "Particle.h"
#include <cmath>

Particle::Particle(int dimensions)
{
	Particle::dimensions = dimensions;
}

void Particle::SetPosition(double* p)
{
	Particle::position = { new double[dimensions] };
	for (size_t i = 0; i < dimensions; i++)
	{
		position[i] = p[i];
	}

}

void Particle::SetVelocity(double* v)
{
	Particle::velocity = { new double[dimensions] };
	for (size_t i = 0; i < dimensions; i++)
	{
		velocity[i] = v[i];
	}

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

double Particle::GetRad()
{
	return std::sqrt(GetMass() / M_PI);
}

Particle::~Particle()
{
	delete position;
	delete velocity;
}