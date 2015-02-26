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

Projection PlaneCollider::Project(const PhysVector3& axis) 
{
	float dotProd = PhysVector3::dot(axis, normal);
	Projection p;
	
	if (abs(dotProd) > 0.999f)
	{
		Vector3 pos = transform.GetPositionVector();
		p.max = pos.x + pos.y + pos.z;
		p.min = p.max;
	}
	else
	{
#define DUMMY
		float m = std::numeric_limits<float>::max DUMMY();
		p.min = -m;
		p.max = m;
	}

	projection = p;
	return p;
}