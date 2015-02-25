#include "RigidBody.h"


void RigidBody::ApplyMomentum(PhysVector3 momentum)
{
	velocity += (momentum * inverseMass);
}

RigidBody::~RigidBody()
{
	delete collider;
}
