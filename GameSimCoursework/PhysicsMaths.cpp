#include "PhysicsMaths.h"
#include <cmath>

//v = u + at
PhysVector3 PhysicsMaths::calculateVelocity(PhysVector3& initialVelocity, PhysVector3& acceleration, float time)
{
	return initialVelocity + (acceleration * time);
}

//s = ut + (1/2)a(t^2)
PhysVector3 PhysicsMaths::calculateDisplacement(PhysVector3& initialVelocity, PhysVector3& acceleration, float time)
{
	return (initialVelocity * time) + ((acceleration * 0.5f) * powf(time, 2));
}