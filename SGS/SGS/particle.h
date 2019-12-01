#pragma once
#include<vector>

class particle
{
private:
    long *position;
    long *velocity;
	long mass;
public:
    particle();
	void SetPosition(long px, long py, long vx, long vy, long mass);
    ~particle();
};