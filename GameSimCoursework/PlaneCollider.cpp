#include "PlaneCollider.h"
#include "PhysicsMaths.h"


bool PlaneCollider::Collides(PhysVector3& contactNormal, const Collider& other, float& penetrationDepth) const
{
	return other.Collides(contactNormal, *this, penetrationDepth);
}

bool PlaneCollider::Collides(PhysVector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const
{
	return PhysicsMaths::CollidesPlaneSphere(other, *this, contactNormal, penetrationDepth);
}

bool PlaneCollider::Collides(PhysVector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const
{
	return false;
}