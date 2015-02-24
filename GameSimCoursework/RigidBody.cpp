#include "RigidBody.h"


RigidBody::~RigidBody()
{
	delete collider;
}
