#include "SphereCollider.h"
#include "../nclgl/Vector3.h"
#include "PhysicsMaths.h"

bool SphereCollider::Collides(Vector3& contactNormal, const Collider& other, float& penetrationDepth) const
{
	return other.Collides(contactNormal, *this, penetrationDepth);
}

bool SphereCollider::Collides(Vector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const
{
	return PhysicsMaths::CollidesSphereSphere(*this, other, contactNormal, penetrationDepth);
}

bool SphereCollider::Collides(Vector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const
{
	return PhysicsMaths::CollidesPlaneSphere(*this, other, contactNormal, penetrationDepth);
}

Projection SphereCollider::Project(const Vector3& axis)
{
	float dotProd = Vector3::Dot(axis, translation);
	Projection p;
	p.max = dotProd + radius;
	p.min = dotProd - radius;
	projection = p;
	return p;
}