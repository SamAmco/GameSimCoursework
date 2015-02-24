#include "SphereCollider.h"
#include "PhysVector3.h"
#include "PhysicsMaths.h"


bool SphereCollider::Collides(PhysVector3& collisionPoint, const Collider& other) const
{
	return other.Collides(collisionPoint, *this);
}

bool SphereCollider::Collides(PhysVector3& collisionPoint, const SphereCollider& other) const
{
	return PhysicsMaths::CollidesSphereSphere(*this, other, collisionPoint);
}

bool SphereCollider::Collides(PhysVector3& collisionPoint, const PlaneCollider& other) const
{
	return PhysicsMaths::CollidesPlaneSphere(*this, other, collisionPoint);
}