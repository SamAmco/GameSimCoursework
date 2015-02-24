#pragma once
#include "Collider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider(PhysVector3 normal) : normal(normal) {}
	~PlaneCollider() {}
	
	bool Collides(PhysVector3& collisionPoint, const Collider& other) const;
	bool Collides(PhysVector3& collisionPoint, const SphereCollider& other) const;
	bool Collides(PhysVector3& collisionPoint, const PlaneCollider& other) const;

	PhysVector3 normal;
};

