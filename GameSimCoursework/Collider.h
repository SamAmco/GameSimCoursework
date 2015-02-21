#pragma once
#include "PhysVector3.h"

class SphereCollider;

class Collider
{
public:
	Collider() {}

	virtual bool Collides(PhysVector3& collisionPoint,
		const SphereCollider& other,
		const PhysVector3& thisPos,
		const PhysVector3& otherPos) const = 0;

	virtual ~Collider() {}
};

