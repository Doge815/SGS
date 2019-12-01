#pragma once
#include<vector>

class particle
{
private:
    long *position;
    long *velocity;
public:
    particle(long x, long y);
    ~particle();
};