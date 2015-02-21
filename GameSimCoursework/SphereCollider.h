#pragma once
#include "Collider.h"

class SphereCollider : Collider
{
public:
	SphereCollider(float radius) : radius(radius) {} 
	~SphereCollider() {}

	bool Collides(PhysVector3& collisionPoint,
		const SphereCollider& other, const PhysVector3& thisPos, const PhysVector3& otherPos) const;

	float radius;
};

