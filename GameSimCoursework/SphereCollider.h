#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(float radius) : radius(radius) {} 
	~SphereCollider() {}

	bool Collides(PhysVector3& collisionPoint, const Collider& other) const;
	bool Collides(PhysVector3& collisionPoint, const SphereCollider& other) const;
	bool Collides(PhysVector3& collisionPoint, const PlaneCollider& other) const;

	float radius;
};

