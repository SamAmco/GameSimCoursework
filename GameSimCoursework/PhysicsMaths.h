#pragma once
#include "PhysVector3.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

class PhysicsMaths
{
public:
	static void semiImplicitEuler(RigidBody& r, PhysVector3 gravity, float time);
	static bool CollidesSphereSphere(const SphereCollider& a, const SphereCollider& b, PhysVector3& contactNormal, float& penetrationDepth);
	static bool CollidesPlaneSphere(const SphereCollider& sphere, const PlaneCollider& plane, PhysVector3& contactNormal, float& penetrationDepth);
private:
	PhysicsMaths();
	~PhysicsMaths();
};

