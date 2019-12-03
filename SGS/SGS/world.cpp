#define _USE_MATH_DEFINES

#include "world.h"
#include "particle.h"
#include <math.h>
#include <iostream>
#include<time.h>

double RandomFloat(double a, double b);

World::World(int numberOfParticles, float area, float massBase)
{
	srand(time(NULL));
	World::numberOfParticles = numberOfParticles;
	World::particles = { new Particle*[numberOfParticles] };
    for (size_t i = 0; i < numberOfParticles; i++)
    {
		double theta	= ((double)rand() / (RAND_MAX));
		double r		= ((double)rand() / (RAND_MAX)* area / 2);
		double m		= ((double)rand() / (RAND_MAX)* M_PI + massBase);

		double px = cos(theta * M_PI * 2) * r + area / 2;
		double py = sin(theta * M_PI * 2) * r + area / 2;

		double vx = (py - area / 2) / 5000;
		double vy = -(px - area / 2) / 5000;
		World::particles[i] = new Particle();
		World::particles[i]->SetPosition(px, py);
		World::particles[i]->SetVelocity(vx,vy);
		World::particles[i]->SetMass(m);
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
		for (size_t u = 0; u < World::numberOfParticles; u++)
		{
			if(i != u && particles[i] != nullptr && particles[u] != nullptr)
			{
				double* p1 = particles[i]->GetPosition();
				double* p2 = particles[u]->GetPosition();
				double r = std::sqrt(std::pow(p2[0] - p1[0], 2) + std::pow(p2[1] - p1[1], 2));

				if(r <= particles[i]->GetRad() + particles[u]->GetRad())
				{
					double* v1 = particles[i]->GetVelocity();
					double  m1 = particles[i]->GetMass();
					double* v2 = particles[u]->GetVelocity();
					double  m2 = particles[u]->GetMass();
					if(m1 > m2)
					{
						v2 = v1;
						p2 = p1;
					}
					particles[u]->SetMass(m1 + m2);
					particles[u]->SetVelocity(v2[0], v2[1]);
					particles[u]->SetPosition(p2[0], p2[1]);
					particles[i] = nullptr;
				}
			}
		}
		
	}
	
    for (size_t i = 0; i < World::numberOfParticles; i++)
    {
		if(particles[i] == nullptr) continue;
		double* v1 = particles[i]->GetVelocity();
		double* p1 = particles[i]->GetPosition();
		double  m1 = particles[i]->GetMass();
		for(size_t u = 0; u < World::numberOfParticles; u++)
		{
			if( i!= u)
			{
				if(particles[u] == nullptr) continue;
				double* p2 = particles[u]->GetPosition();
				double  m2 = particles[u]->GetMass();

				double r = std::sqrt(std::pow(p2[0] - p1[0], 2) + std::pow(p2[1] - p1[1], 2));
				
				double f = m1 * m2 / std::pow(r, 2) / 1000;
				double a = std::atan2(p2[1] - p1[1], p2[0] - p1[0]);
				double fx = std::cos(a) * f;
				double fy = std::sin(a) * f;
				v1[0] += fx;
				v1[1] += fy;
			}
		}
		particles[i]->SetVelocity(v1[0], v1[1]);
		skip:;
	}
	for (size_t i = 0; i < World::numberOfParticles; i++)
	{
		if(particles[i] == nullptr) continue;
		double* v = particles[i]->GetVelocity();
		double* p = particles[i]->GetPosition();
		particles[i]->SetPosition(v[0] + p[0], v[1] + p[1]);
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