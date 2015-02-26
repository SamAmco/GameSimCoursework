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
	Projection p;
	
	//For most cases we want to planes to be compared with everything.
	//it is rare that their projection against any axis is not infinite.
#define DUMMY
	float m = std::numeric_limits<float>::max DUMMY();
	p.min = -m;
	p.max = m;

	projection = p;
	return p;
}