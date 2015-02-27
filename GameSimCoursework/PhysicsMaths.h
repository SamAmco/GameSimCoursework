#pragma once
#include "../nclgl/Vector3.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

//This is a global constant that defines the threshold for velocity below which an object can
//be considered at rest.
const float REST_THRESHOLD = 0.001f;

class PhysicsMaths
{
public:
	static void semiImplicitEuler(RigidBody& r, Vector3 gravity, float time);
	//These Two functions define whether or not a given sphere is colliding with a given plane or sphere
	//It is useful to put them here so that the functionality only has to be written once.
	static bool CollidesSphereSphere(const SphereCollider& a, const SphereCollider& b, Vector3& contactNormal, float& penetrationDepth);
	static bool CollidesPlaneSphere(const SphereCollider& sphere, const PlaneCollider& plane, Vector3& contactNormal, float& penetrationDepth);
private:
	//This class is strictly static so the constructor is private.
	PhysicsMaths();
	~PhysicsMaths();
};

