#pragma once
#include "PhysVector3.h"
#include "RigidBody.h"

class PhysicsMaths
{
public:
	static void semiImplicitEuler(RigidBody& r, float time);
private:
	PhysicsMaths();
	~PhysicsMaths();
};

