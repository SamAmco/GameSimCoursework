#include "PlaneCollider.h"
#include "PhysicsMaths.h"


bool PlaneCollider::Collides(PhysVector3& collisionPoint, const Collider& other) const
{
	return other.Collides(collisionPoint, *this);
}

bool PlaneCollider::Collides(PhysVector3& collisionPoint, const SphereCollider& other) const
{
	return PhysicsMaths::CollidesPlaneSphere(other, *this, collisionPoint);
}

bool PlaneCollider::Collides(PhysVector3& collisionPoint, const PlaneCollider& other) const
{
	return false;
}