#include "particle.h"

particle::particle(long x, long y)
{
    particle::position = {new long[2]{x, y}};
    particle::velocity = {new long[2]{0, 0}};
}

particle::~particle()
{
    delete position;
    delete velocity;
}