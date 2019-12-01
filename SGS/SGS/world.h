#pragma once
#include<vector>
#include"particle.h"

class world
{
private:
    std::vector<particle *> *particles;
public:
    world(int numberOfParticles);
    void Step();
    std::vector<particle> GetParticles();
    ~world();
};