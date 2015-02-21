#pragma once
#include "PhysVector3.h"
#include "SphereCollider.h"

class RigidBody
{
public:
	RigidBody(PhysVector3 position = PhysVector3::zero(),
		PhysVector3 acceleration = PhysVector3::zero(),
		PhysVector3 velocity = PhysVector3::zero(),
		float mass = 1)
			: position(position),
			acceleration(acceleration),
			velocity(velocity),
			mass(mass),
			sphereCollider(SphereCollider(0)) {}

	virtual ~RigidBody();

	PhysVector3 position;
	PhysVector3 acceleration;
	PhysVector3 velocity;
	SphereCollider sphereCollider;
	float mass;
};

