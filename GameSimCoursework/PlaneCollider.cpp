#include "PlaneCollider.h"
#include "PhysicsMaths.h"

//This allows us to check collision between two arbitrary colliders and have them work out what the specific
//collision detection function that needs to be called is
bool PlaneCollider::Collides(Vector3& contactNormal, const Collider& other, float& penetrationDepth) const
{
	return other.Collides(contactNormal, *this, penetrationDepth);
}

//All collision functionality is defined in PhysicsMaths
bool PlaneCollider::Collides(Vector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const
{
	return PhysicsMaths::CollidesPlaneSphere(other, *this, contactNormal, penetrationDepth);
}

//All collision functionality is defined in PhysicsMaths
bool PlaneCollider::Collides(Vector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const
{
	return false;
}

//This function allows us to cache a projection for this collider as it is now for use in sort and sweep.
Projection PlaneCollider::Project(const Vector3& axis) 
{
	Projection p;
	
	//For most cases we want planes to be compared with everything.
	//it is rare that their projection against any axis is not infinite.
	//There is one rare exception where the axis is perpendicular to the 
	//plane, however the amount of time saved for this simulation in doing that
	//check would be negligable. 
#define DUMMY
	float m = std::numeric_limits<float>::max DUMMY();
	p.min = -m;
	p.max = m;

	projection = p;
	return p;
}