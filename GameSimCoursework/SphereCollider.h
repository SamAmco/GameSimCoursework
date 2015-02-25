#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(float radius) : radius(radius) {} 
	~SphereCollider() {}

	bool Collides(PhysVector3& contactNormal, const Collider& other, float& penetrationDepth) const;
	bool Collides(PhysVector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const;
	bool Collides(PhysVector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const;


	float radius;
};

