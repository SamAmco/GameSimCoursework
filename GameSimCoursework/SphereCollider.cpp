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
	//bool b = PhysicsMaths::CollidesPlaneSphere(*this, other, contactNormal, penetrationDepth);
	//if (b)
	//{
	//	Projection p = other.Project(PhysVector3(0, 1, 0));
	//	std::cout << p.min << " : " << p.max << std::endl;
	//}
	return PhysicsMaths::CollidesPlaneSphere(*this, other, contactNormal, penetrationDepth);
}

Projection SphereCollider::Project(const PhysVector3& axis)
{
	float dotProd = PhysVector3::dot(axis, transform.GetPositionVector());
	Projection p;
	p.max = dotProd + radius;
	p.min = dotProd - radius;
	projection = p;
	return p;
}