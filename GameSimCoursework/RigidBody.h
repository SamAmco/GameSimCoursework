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
			isAtRest(false),
			drag(0.99f),
			restFrames(0),
			lastDisp(Vector3()){}

	virtual ~RigidBody();

	void ApplyMomentum(Vector3 momentum);

	Vector3 acceleration;
	Vector3 velocity;
	Collider* collider;
	float drag;
	float inverseMass;
	bool isKinematic;
	bool isAtRest;
	int restFrames = 0;
	Vector3 lastDisp;
};

