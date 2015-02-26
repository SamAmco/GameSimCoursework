#include "RigidBody.h"


void RigidBody::ApplyMomentum(Vector3 momentum)
{
	velocity += (momentum * inverseMass);
}

RigidBody::~RigidBody()
{
	delete collider;
}
