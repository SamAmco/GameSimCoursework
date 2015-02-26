#pragma once
#include "../nclgl/Vector3.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

class PhysicsMaths
{
public:
	static void semiImplicitEuler(RigidBody& r, Vector3 gravity, float time);
	static bool CollidesSphereSphere(const SphereCollider& a, const SphereCollider& b, Vector3& contactNormal, float& penetrationDepth);
	static bool CollidesPlaneSphere(const SphereCollider& sphere, const PlaneCollider& plane, Vector3& contactNormal, float& penetrationDepth);
private:
	PhysicsMaths();
	~PhysicsMaths();
};

