#pragma once
#include "Collider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider(Vector3 normal) : normal(normal) {}
	~PlaneCollider() {}
	
	virtual bool Collides(Vector3& contactNormal, const Collider& other, float& penetrationDepth) const;
	virtual bool Collides(Vector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const;
	virtual bool Collides(Vector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const;
	virtual Projection Project(const Vector3& axis);

	Vector3 normal;
};

