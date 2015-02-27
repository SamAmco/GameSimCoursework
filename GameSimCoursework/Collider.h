#pragma once
#include "../nclgl/Vector3.h"
#include "../nclgl/Matrix4.h"

//Forward declare these to break the circular dependency
class SphereCollider;
class PlaneCollider;

//This is used for sort and sweep
struct Projection
{
	float min, max;
};

//A collider can be of many forms, but I use this abstract class so that we can check collisions between any two
//colliders without having to know what they are. It is useful to have it seperate from RigidBody so that we don't 
//need a RigidBody to have a collider (this could be used for objects that are solid and don't react to physics 
//but need to deflect other physics objects).
class Collider
{
public:
	Collider() { }

	virtual bool Collides(Vector3& contactNormal, const Collider& other, float& penetrationDepth) const = 0;
	virtual bool Collides(Vector3& contactNormal, const SphereCollider& other, float& penetrationDepth) const = 0;
	virtual bool Collides(Vector3& contactNormal, const PlaneCollider& other, float& penetrationDepth) const = 0;
	virtual Projection Project(const Vector3& axis) = 0;

	//Any collider has a position in space and can be projected for sort and sweep
	//Note that it may be more efficient for a plane to store only a value d as the distance from
	//the origin, instead of calculating this from a translation vector, however using a translation
	//for all colliders arguably makes the model more extendable 
	Vector3 translation;
	Projection projection;

	virtual ~Collider() {}
};

