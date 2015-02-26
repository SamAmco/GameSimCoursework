#pragma once
#include "PhysVector3.h"
#include "../nclgl/Matrix4.h"

class SphereCollider;
class PlaneCollider;

struct Projection
{
	float min, max;
};

class Collider
{
public:
	Collider(Matrix4 transform = Matrix4()) : transform(transform) { }

	virtual bool Collides(PhysVector3& contactNormal, const Collider& other, float& penetrationDepth) const = 0;
	virtual bool Collides(PhysVector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const = 0;
	virtual bool Collides(PhysVector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const = 0;
	virtual Projection Project(const PhysVector3& axis) = 0;

	Matrix4 transform;
	Projection projection;

	virtual ~Collider() {}
};

