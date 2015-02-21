#include "SphereCollider.h"
#include "PhysVector3.h"


bool SphereCollider::Collides(PhysVector3& collisionPoint,
	const SphereCollider& other, const PhysVector3& thisPos, const PhysVector3& otherPos) const
{
	//squaring d is more efficient than finding the square root of the sqrMagnitude
	float d = radius + other.radius;
	PhysVector3 norm = thisPos - otherPos;
	if (norm.sqrMagnitude() < d * d)
	{
		float p = (radius + other.radius) - d;
		norm.normalise();
		collisionPoint = thisPos - (norm * (other.radius - p));
		return true;
	}
	return false;
}
