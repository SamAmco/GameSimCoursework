#pragma once
#include "Collider.h"

//A sphere collider is a type of collider that simply holds a radius
class SphereCollider : public Collider
{
public:
	SphereCollider(float radius) : radius(radius) {} 
	~SphereCollider() {}

	virtual bool Collides(Vector3& contactNormal, const Collider& other, float& penetrationDepth) const;
	virtual bool Collides(Vector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const;
	virtual bool Collides(Vector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const;
	virtual Projection Project(const Vector3& axis);

	float radius;
};

