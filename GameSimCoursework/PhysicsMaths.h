#pragma once
#include "PhysVector3.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

class PhysicsMaths
{
public:
	static void semiImplicitEuler(RigidBody& r, float time);
	static bool CollidesSphereSphere(const SphereCollider& a, const SphereCollider& b, PhysVector3& collisionPoint);
	static bool CollidesPlaneSphere(const SphereCollider& sphere, const PlaneCollider& plane, PhysVector3& collisionPoint);
private:
	PhysicsMaths();
	~PhysicsMaths();
};

