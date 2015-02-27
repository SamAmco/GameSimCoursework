#include "SphereCollider.h"
#include "PhysicsMaths.h"

//This allows us to check collision between two arbitrary colliders and have them work out what the specific
//collision detection function that needs to be called is
bool SphereCollider::Collides(Vector3& contactNormal, const Collider& other, float& penetrationDepth) const
{
	return other.Collides(contactNormal, *this, penetrationDepth);
}

//All collision functionality is defined in PhysicsMaths
bool SphereCollider::Collides(Vector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const
{
	return PhysicsMaths::CollidesSphereSphere(*this, other, contactNormal, penetrationDepth);
}

//All collision functionality is defined in PhysicsMaths
bool SphereCollider::Collides(Vector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const
{
	return PhysicsMaths::CollidesPlaneSphere(*this, other, contactNormal, penetrationDepth);
}

//This function allows us to cache a projection for this collider as it is now for use in sort and sweep.
Projection SphereCollider::Project(const Vector3& axis)
{
	//The projection should contain the minimum and maximum values that a sphere collider can reach
	//on a given axis. To find this, we project the position of the sphere onto the axis and then take 
	//the radius either side to find min and max.
	float dotProd = Vector3::Dot(axis, translation);
	Projection p;
	p.max = dotProd + radius;
	p.min = dotProd - radius;
	projection = p;
	return p;
}