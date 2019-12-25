#define _USE_MATH_DEFINES

#include "World.h"
#include "Particle.h"
#include <math.h>
#include <iostream>
#include<time.h>

double RandomFloat(double a, double b);

World::World(int dimensions)
{
	srand(time(NULL));
	World::numberOfParticles = 0;
	particles = { new Particle * [0] };
	World::dimensions = dimensions;
}

void World::InitWorld(int numberOfParticles, float massBase, float area)
{
	srand(time(NULL));
	World::numberOfParticles = numberOfParticles;
	particles = { new Particle * [numberOfParticles] };
	for (size_t i = 0; i < numberOfParticles; i++)
	{
		double* pos = { new double[dimensions] };

		double distSq = 0;

		while (true)
		{
			distSq = 0;
			for (size_t u = 0; u < dimensions; u++)
			{
				pos[u] = ((double)rand()) / (double)RAND_MAX * 2 - 1;
			}

			for (size_t u = 0; u < dimensions; u++) {
				distSq += pos[u] * pos[u];
			}

			if (distSq <= 1) break;
		}
		double dist = std::sqrt(distSq) * area / 2;

		for (size_t u = 0; u < dimensions; u++)
		{
			pos[u] *= dist;
		}
		double* vel = { new double[dimensions] };
		for (size_t u = 0; u < dimensions; u++)
		{
			auto p = pos[(u + 1) % dimensions] / 4000;

			if (u % 2 == 0) vel[u] = p;
			else vel[u] = -p;
		}
		World::particles[i] = new Particle(dimensions);
		World::particles[i]->SetPosition(pos);
		World::particles[i]->SetVelocity(vel);
		World::particles[i]->SetMass(massBase);
	}
}

World::~World()
{
	delete[] World::particles;
}

void World::AddParticle(Particle* p)
{
	Particle** ps = GetParticles();
	particles = { new Particle * [numberOfParticles + 1] };
	for (size_t i = 0; i < numberOfParticles; i++)
	{
		particles[i] = ps[i];
	}
	particles[numberOfParticles] = p;
	numberOfParticles++;
}

void World::Step()
{
	MergeParticles();
	CalcVelocity();
	ApplyVelocity();
}

int World::GetDimensions()
{
	return dimensions;
}

void World::MergeParticles()
{
	for (size_t i = 0; i < numberOfParticles; i++)
	{
		for (size_t u = 0; u < numberOfParticles; u++)
		{
			if (i != u && particles[i] != nullptr && particles[u] != nullptr)
			{
				double* p1 = particles[i]->GetPosition();
				double* p2 = particles[u]->GetPosition();
				double r = 0;
				for (size_t o = 0; o < dimensions; o++)
				{
					r += std::pow(p2[o] - p1[o], 2);
				}

				r = std::sqrt(r);

				if (r <= particles[i]->GetRad() + particles[u]->GetRad())
				{
#if false
					double* v1 = particles[i]->GetVelocity();
					double  m1 = particles[i]->GetMass();
					double* v2 = particles[u]->GetVelocity();
					double  m2 = particles[u]->GetMass();
					if (m1 > m2)
					{
						v2 = v1;
						p2 = p1;
					}
					particles[u]->SetMass(m1 + m2);
					particles[u]->SetVelocity(v2);
					particles[u]->SetPosition(p2);
					particles[i] = nullptr;
#else
					double* v = { new double[dimensions] };
					double* v1 = particles[i]->GetVelocity();
					double  m1 = particles[i]->GetMass();
					double* v2 = particles[u]->GetVelocity();
					double  m2 = particles[u]->GetMass();
					for (size_t o = 0; o < dimensions; o++)
					{
						double Eges = (m1 * std::pow(v1[o], 2) / 2) + (m2 * std::pow(v2[o], 2) / 2);
						if (Eges >= 0)
						{
							v[o] = std::sqrt(2 * Eges / (m1 + m2));
						}
						else
						{
							v[o] = -std::sqrt(2 * -Eges / (m1 + m2));
						}
					}
					particles[i]->SetMass(m1 + m2);
					particles[i]->SetVelocity(v);
					if (m2 > m1)
					{
						particles[i]->SetPosition(p2);
					}
					particles[u] = nullptr;
#endif
				}
			}
		}

	}
}

void World::CalcVelocity()
{
	for (size_t i = 0; i < World::numberOfParticles; i++)
	{
		if (particles[i] == nullptr) continue;
		double* v1 = particles[i]->GetVelocity();
		double* p1 = particles[i]->GetPosition();
		double  m1 = particles[i]->GetMass();
		for (size_t u = 0; u < World::numberOfParticles; u++)
		{
			if (i != u)
			{
				if (particles[u] == nullptr) continue;
				double* p2 = particles[u]->GetPosition();
				double  m2 = particles[u]->GetMass();

				double xDiff = p2[0] - p1[0];
				double yDiff = p2[1] - p1[1];

				double r = xDiff * xDiff + yDiff * yDiff;

				const double G = 0.001;
				const double E = 200;

				double forceFac = G * m2 / std::pow(r + E, 1.5);

				v1[0] += xDiff * forceFac;
				v1[1] += yDiff * forceFac;
			}
		}
		particles[i]->SetVelocity(v1);
	skip:;
	}
}

void World::ApplyVelocity()
{
	for (size_t i = 0; i < World::numberOfParticles; i++)
	{
		if (particles[i] == nullptr) continue;
		double* v = particles[i]->GetVelocity();
		double* p = particles[i]->GetPosition();
		for (size_t u = 0; u < dimensions; u++)
		{
			p[u] += v[u];
		}
		particles[i]->SetPosition(p);
	}
}

int World::GetNumberOfParticles()
{
	return World::numberOfParticles;
}

Particle** World::GetParticles()
{
	return World::particles;
}