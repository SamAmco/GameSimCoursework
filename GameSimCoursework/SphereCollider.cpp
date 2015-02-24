#include "SphereCollider.h"
#include "PhysVector3.h"
#include "PhysicsMaths.h"


bool SphereCollider::Collides(PhysVector3& contactNormal, const Collider& other) const
{
	return other.Collides(contactNormal, *this);
}

bool SphereCollider::Collides(PhysVector3& contactNormal, const SphereCollider& other) const
{
	return PhysicsMaths::CollidesSphereSphere(*this, other, contactNormal);
}

bool SphereCollider::Collides(PhysVector3& contactNormal, const PlaneCollider& other) const
{
	return PhysicsMaths::CollidesPlaneSphere(*this, other, contactNormal);
}