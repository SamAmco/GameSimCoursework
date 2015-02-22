#pragma once
#include "PhysVector3.h"
#include "SphereCollider.h"

class RigidBody
{
public:
	RigidBody(PhysVector3 acceleration = PhysVector3::zero(),
		PhysVector3 velocity = PhysVector3::zero(),
		float mass = 1)
			: acceleration(acceleration),
			velocity(velocity),
			mass(mass),
			collider(NULL) {}

	virtual ~RigidBody();

	PhysVector3 acceleration;
	PhysVector3 velocity;
	Collider* collider;
	float mass;
};

