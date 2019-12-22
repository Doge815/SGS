#define _USE_MATH_DEFINES

#include "Particle.h"
#include <cmath>

#pragma region Con-/Destructor
Particle::Particle(int dimensions)
{
	Particle::dimensions = dimensions;
}

Particle::~Particle()
{
	delete position;
	delete velocity;
}
#pragma endregion Con-/Destructor

#pragma region Gets&Sets
inline void Particle::SetPosition(double* p)
{
	Particle::position = { new double[dimensions] };
	for (size_t i = 0; i < dimensions; i++)
	{
		position[i] = p[i];
	}

}

inline void Particle::SetVelocity(double* v)
{
	Particle::velocity = { new double[dimensions] };
	for (size_t i = 0; i < dimensions; i++)
	{
		velocity[i] = v[i];
	}

}

inline void Particle::SetMass(double mass)
{
	Particle::mass = mass;
}

inline double* Particle::GetPosition()
{
	return Particle::position;
}

inline double* Particle::GetVelocity()
{
	return Particle::velocity;
}

inline double Particle::GetMass()
{
	return Particle::mass;
}

inline double Particle::GetRad()
{
	//TODO: All DIMS!
	return std::sqrt(GetMass() / M_PI);
}
#pragma endregion Gets&Sets