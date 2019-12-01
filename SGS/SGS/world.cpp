#include "world.h"

world::world(int numberOfParticles)
{
    for (size_t i = 0; i < numberOfParticles; i++)
    {
        world::particles->push_back(new particle(0,0));
    }
    
}

world::~world()
{
    for (size_t i = 0; i < world::particles->size(); i++)
    {
        delete world::particles->back();
    }
    
}



void world::Step()
{
    for (size_t i = 0; i < world::particles->size(); i++)
    {
    }
}