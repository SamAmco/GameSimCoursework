#include "RigidBody.h"


void RigidBody::ApplyMomentum(Vector3 momentum)
{
	velocity += (momentum * inverseMass);
	isAtRest = false;
}

RigidBody::~RigidBody()
{
}
