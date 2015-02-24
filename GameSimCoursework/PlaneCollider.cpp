#include "PlaneCollider.h"
#include "PhysicsMaths.h"


bool PlaneCollider::Collides(PhysVector3& contactNormal, const Collider& other) const
{
	return other.Collides(contactNormal, *this);
}

bool PlaneCollider::Collides(PhysVector3& contactNormal, const SphereCollider& other) const
{
	return PhysicsMaths::CollidesPlaneSphere(other, *this, contactNormal);
}

bool PlaneCollider::Collides(PhysVector3& contactNormal, const PlaneCollider& other) const
{
	return false;
}