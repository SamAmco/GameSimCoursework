#include "PhysicsMaths.h"
#include "../nclgl/Vector3.h"

//Each frame we update each RigidBody with regard to its acceleration, velocity and gravity
void PhysicsMaths::semiImplicitEuler(RigidBody& r, Vector3 gravity, float time)
{
	r.velocity = (r.velocity + ((r.acceleration + gravity) * time)) * r.drag;

	//We need to precalculate what the new displacement will be to use it in our rest
	//detection, but we only apply it if the body is not now considered at rest.
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

	//if the object is not at rest, then update it's position and last displacement
	r.collider->translation = disp;
	r.lastDisp = r.collider->translation;
}

//Returns true if the two spheres collide, but also sets the value of the contact normal
//and penetration depth for the collision. 
bool PhysicsMaths::CollidesSphereSphere(const SphereCollider& a,
	const SphereCollider& b, Vector3& contactNormal, float& penetrationDepth)
{
	//Two spheres are colliding if the sum of their radii is greater than the distance between
	//their centre's
	float d = a.radius + b.radius;
	Vector3 norm = a.translation - b.translation;
	float dist = (norm).Length();
	if (dist < d)
	{
		//THE TWO SPHERE'S ARE COLLIDING
		//penetration depth is then the sum of the radii minus the distance between their centre's
		//the contact normal is just the normalised direction from one to the other.
		penetrationDepth = (a.radius + b.radius) - dist;
		contactNormal = norm.Normalised();
		return true;
	}
	return false;
}

//Returns true if the given plane and sphere collide, but also sets the value of the contact normal
//and penetration depth for the collision.
bool PhysicsMaths::CollidesPlaneSphere(const SphereCollider& sphere,
	const PlaneCollider& plane, Vector3& contactNormal, float& penetrationDepth)
{
	//The two are colliding if the dot product between the plane normal and the sphere's translation
	// plus the distance of the plane from the origin is smaller than the sphere's radius.
	Vector3 norm = plane.normal;
	float dist = Vector3::Dot(norm, sphere.translation) + plane.translation.Length();

	if (dist < sphere.radius)
	{
		//THE TWO HAVE COLLIDED
		//Penetration depth and contact normal are trivial here.
		penetrationDepth = (sphere.radius - dist);
		contactNormal = norm.Normalised();
		return true;
	}
	return false;
}