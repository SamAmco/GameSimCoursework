#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(float radius) : radius(radius) {} 
	~SphereCollider() {}

	bool Collides(PhysVector3& contactNormal, const Collider& other) const;
	bool Collides(PhysVector3& contactNormal, const SphereCollider& other) const;
	bool Collides(PhysVector3& contactNormal, const PlaneCollider& other) const;

	float radius;
};

