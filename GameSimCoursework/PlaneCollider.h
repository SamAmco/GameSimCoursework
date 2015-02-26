#pragma once
#include "Collider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider(PhysVector3 normal) : normal(normal) {}
	~PlaneCollider() {}
	
	virtual bool Collides(PhysVector3& contactNormal, const Collider& other, float& penetrationDepth) const;
	virtual bool Collides(PhysVector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const;
	virtual bool Collides(PhysVector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const;
	virtual Projection Project(const PhysVector3& axis);

	PhysVector3 normal;
};

