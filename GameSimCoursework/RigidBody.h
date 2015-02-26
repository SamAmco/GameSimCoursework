#pragma once
#include "../nclgl/Vector3.h"
//#include "Collider.h"

class Collider;

class RigidBody
{
public:
	RigidBody(Vector3 acceleration = Vector3(),
		Vector3 velocity = Vector3(),
		float mass = 1)
			: acceleration(acceleration),
			velocity(velocity),
			inverseMass(1.0f / mass),
			collider(NULL),
			isKinematic(false),
			drag(0.99f){}

	virtual ~RigidBody();

	void ApplyMomentum(Vector3 momentum);

	Vector3 acceleration;
	Vector3 velocity;
	Collider* collider;
	float drag;
	float inverseMass;
	bool isKinematic;
};

