#pragma once
#include "PhysVector3.h"

class PhysicsMaths
{
public:
	static PhysVector3 calculateVelocity(PhysVector3& initialVelocity, PhysVector3& acceleration, float time);
	static PhysVector3 calculateDisplacement(PhysVector3& initialVelocity, PhysVector3& acceleration, float time);
private:
	PhysicsMaths();
	~PhysicsMaths();
};

