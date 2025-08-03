#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>

// Use <cmath> in C++ if you prefer: #include <cmath>
// And optionally: using std::pow, std::sqrt;

float maxf(float a, float b);

float W(float r, float h);
float WNear(float r, float h);

void calcPressure(float particles[], int numOfParticles, int offset, int index, float h);

void D(float particles[], int numOfParticles, int offset, int indexI, int indexJ, float h, float deltaTime, float outVec[3]);

void updateParticle(float particles[], int numOfParticles, int offset, int index, float h, float deltaTime);

void update(float particles[], int numOfParticles, int offset, float h, float deltaTime);

#endif // PHYSICS_H
