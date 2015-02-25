#include "SphereCollider.h"
#include "PhysVector3.h"
#include "PhysicsMaths.h"


bool SphereCollider::Collides(PhysVector3& contactNormal, const Collider& other, float& penetrationDepth) const
{
	return other.Collides(contactNormal, *this, penetrationDepth);
}

bool SphereCollider::Collides(PhysVector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const
{
	return PhysicsMaths::CollidesSphereSphere(*this, other, contactNormal, penetrationDepth);
}

bool SphereCollider::Collides(PhysVector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const
{
	return PhysicsMaths::CollidesPlaneSphere(*this, other, contactNormal, penetrationDepth);
}