#include "PhysicsMaths.h"
#include "../nclgl/Vector3.h"

void PhysicsMaths::semiImplicitEuler(RigidBody& r, Vector3 gravity, float time)
{
	r.velocity = (r.velocity + ((r.acceleration + gravity) * time)) * r.drag;

	Vector3 disp = r.collider->translation + (r.velocity * time);

	//If the object has barely moved for 10 frames then set it to rest
	if (((disp - r.lastDisp) / time).sqrLength() < REST_THRESHOLD)
	{
		++r.restFrames;
		if (r.restFrames > 10)
		{
			r.isAtRest = true;
			return;
		}
	}
	else
		r.restFrames = 0;

	r.collider->translation = disp;
	r.lastDisp = r.collider->translation;
}

bool PhysicsMaths::CollidesSphereSphere(const SphereCollider& a,
	const SphereCollider& b, Vector3& contactNormal, float& penetrationDepth)
{
	float d = a.radius + b.radius;
	Vector3 norm = a.translation - b.translation;
	float dist = (norm).Length();
	if (dist < d)
	{
		penetrationDepth = (a.radius + b.radius) - dist;
		norm.Normalise();
		contactNormal = norm;
		return true;
	}
	return false;
}

bool PhysicsMaths::CollidesPlaneSphere(const SphereCollider& sphere,
	const PlaneCollider& plane, Vector3& contactNormal, float& penetrationDepth)
{
	Vector3 norm = plane.normal;
	float dotProd = Vector3::Dot(norm, sphere.translation);

	if (dotProd + plane.translation.Length() < sphere.radius)
	{
		penetrationDepth = (sphere.radius - (dotProd + plane.translation.Length()));
		norm.Normalise();
		contactNormal = norm;
		return true;
	}
	return false;
}