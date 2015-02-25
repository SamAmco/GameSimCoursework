#pragma once
#include "PhysVector3.h"
//#include "Collider.h"

class Collider;

class RigidBody
{
public:
	RigidBody(PhysVector3 acceleration = PhysVector3::zero(),
		PhysVector3 velocity = PhysVector3::zero(),
		float mass = 1)
			: acceleration(acceleration),
			velocity(velocity),
			inverseMass(1.0f / mass),
			collider(NULL),
			isKinematic(false),
			drag(0.99f){}

	virtual ~RigidBody();

	void ApplyMomentum(PhysVector3 momentum);

	PhysVector3 acceleration;
	PhysVector3 velocity;
	Collider* collider;
	float drag;
	float inverseMass;
	bool isKinematic;
};

