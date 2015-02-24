#pragma once
#include "Collider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider(PhysVector3 normal) : normal(normal) {}
	~PlaneCollider() {}
	
	bool Collides(PhysVector3& contactNormal, const Collider& other) const;
	bool Collides(PhysVector3& contactNormal, const SphereCollider& other) const;
	bool Collides(PhysVector3& contactNormal, const PlaneCollider& other) const;

	PhysVector3 normal;
};

