#include "SphereCollider.h"
#include "PhysVector3.h"


bool SphereCollider::Collides(PhysVector3& collisionPoint, const Collider& other) const
{
	return other.Collides(collisionPoint, *this);
}

bool SphereCollider::Collides(PhysVector3& collisionPoint, const SphereCollider& other) const
{
	//squaring d is more efficient than finding the square root of the sqrMagnitude
	float d = radius + other.radius;
	PhysVector3 pos = transform.GetPositionVector();
	PhysVector3 norm = pos - PhysVector3(other.transform.GetPositionVector());
	if (norm.sqrMagnitude() < d * d)
	{
		float p = (radius + other.radius) - d;
		norm.normalise();
		collisionPoint = pos - (norm * (other.radius - p));
		return true;
	}
	return false;
}
