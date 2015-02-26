#pragma once
#include "../nclgl/Vector3.h"
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
	Collider(Matrix4 transform = Matrix4()) : translation(translation) { }

	virtual bool Collides(Vector3& contactNormal, const Collider& other, float& penetrationDepth) const = 0;
	virtual bool Collides(Vector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const = 0;
	virtual bool Collides(Vector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const = 0;
	virtual Projection Project(const Vector3& axis) = 0;

	Vector3 translation;
	Projection projection;

	virtual ~Collider() {}
};

