#include "PhysicsMaths.h"
#include "../nclgl/Vector3.h"

void PhysicsMaths::semiImplicitEuler(RigidBody& r, PhysVector3 gravity, float time)
{
	r.velocity = (r.velocity + ((r.acceleration + gravity) * time)) * r.drag;
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
	Matrix4 m1 = Matrix4::Translation(Vector3(plane.normal.getX(), plane.normal.getY(), plane.normal.getZ()));
	Matrix4 m2 = plane.transform;
	m2.SetPositionVector(Vector3(0,0,0));
	PhysVector3 normal = (m2 * m1).GetPositionVector();
	//std::cout << normal << std::endl;

	float dotProd = PhysVector3::dot(normal, sphere.transform.GetPositionVector());

	if (dotProd + plane.transform.GetPositionVector().Length() < sphere.radius)
	{
		//p = r - (N.S + d)
		penetrationDepth = (sphere.radius - (dotProd + plane.transform.GetPositionVector().Length()));
		contactNormal = normal.normalise();
		return true;
	}
	return false;
}