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
	const SphereCollider& b, PhysVector3& contactNormal)
{
	//squaring d is more efficient than finding the square root of the sqrMagnitude
	float d = a.radius + b.radius;
	PhysVector3 pos = a.transform.GetPositionVector();
	PhysVector3 norm = pos - PhysVector3(b.transform.GetPositionVector());
	if (norm.sqrMagnitude() < d * d)
	{
		//float p = (a.radius + b.radius) - d;
		contactNormal = norm.normalise();
		//PhysVector3 P = pos - (norm * (b.radius - p));
		return true;
	}
	return false;
}

bool PhysicsMaths::CollidesPlaneSphere(const SphereCollider& sphere,
	const PlaneCollider& plane, PhysVector3& contactNormal)
{
	float dotProd = PhysVector3::dot(plane.normal, sphere.transform.GetPositionVector());

	if (dotProd + plane.transform.GetPositionVector().Length() < sphere.radius)
	{
		PhysVector3 norm = plane.normal;
		contactNormal = norm.normalise();
		return true;
	}
	return false;
}