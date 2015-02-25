#include "PhysicsMaths.h"
#include "../nclgl/Vector3.h"

void PhysicsMaths::semiImplicitEuler(RigidBody& r, float time)
{
	r.velocity = r.velocity + (r.acceleration * time);
	PhysVector3 disp = r.collider->transform.GetPositionVector();
	disp = disp + (r.velocity * time);
	r.collider->transform.SetPositionVector(Vector3(disp.getX(), disp.getY(), disp.getZ()));
}

bool PhysicsMaths::CollidesSphereSphere(const SphereCollider& a,
	const SphereCollider& b, PhysVector3& contactNormal, float& penetrationDepth)
{
	//squaring d is more efficient than finding the square root of the sqrMagnitude
	float d = a.radius + b.radius;
	PhysVector3 norm = a.transform.GetPositionVector() - b.transform.GetPositionVector();
	float dist = (norm).getMagnitude();
	if (dist < d)
	{
		penetrationDepth = (a.radius + b.radius) - dist;
		contactNormal = norm.normalise();
		//PhysVector3 P = pos - (norm * (b.radius - p));
		return true;
	}
	return false;
}

bool PhysicsMaths::CollidesPlaneSphere(const SphereCollider& sphere,
	const PlaneCollider& plane, PhysVector3& contactNormal, float& penetrationDepth)
{
	float dotProd = PhysVector3::dot(plane.normal, sphere.transform.GetPositionVector());

	if (dotProd + plane.transform.GetPositionVector().Length() < sphere.radius)
	{
		PhysVector3 norm = plane.normal;
		//p = r - (N.S + d)
		penetrationDepth = (sphere.radius - (dotProd + plane.transform.GetPositionVector().Length()));
		contactNormal = norm;
		return true;
	}
	return false;
}