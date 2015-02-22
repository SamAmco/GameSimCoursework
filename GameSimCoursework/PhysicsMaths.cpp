#include "PhysicsMaths.h"
#include "../nclgl/Vector3.h"

void PhysicsMaths::semiImplicitEuler(RigidBody& r, float time)
{
	r.velocity = r.velocity + (r.acceleration * time);
	PhysVector3 disp = r.collider->transform.GetPositionVector();
	disp = disp + (r.velocity * time);
	r.collider->transform.SetPositionVector(Vector3(disp.getX(), disp.getY(), disp.getZ()));
}