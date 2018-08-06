#pragma once
#include "../nclgl/Vector3.h"

//This is to break a circular dependency
class Collider;

//A RigidBody defines a physical entity in the world that is affected by forces
//such as gravity and collisions. It's position and velocity will be updated per
//frame unless it is either Kinematic or at rest.
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

	//Used to apply an impulse to an object 
	void ApplyMomentum(Vector3 momentum);

	Vector3 acceleration;
	Vector3 velocity;
	
	//A RigidBody stores a pointer to a Collider, which allows that Collider to be polymorphic.
	//A RigidBody should not be concerned with the form of it's collider, but it should always have one. 
	Collider* collider;

	//drag is used to dampen the velocity of a RigidBody per frame.
	float drag;

	//We can store mass as inverse mass to save on the time it takes to calculate the inverse mass of the RigidBody
	//since we only really ever need the inverse mass for the purpose of this simulation
	float inverseMass;

	//If ia RigidBody is kinematic, then it acts similarly to a static collider without a RigidBody. In most physics
	//simulations this would be used to model things like solid anchors in chains or springs. i.e. We need a RigidBody 
	//because it must have a joint attatched, but we don't want it to act like a regular RigidBody. Here I have used it 
	//so that Plane's can still be modelled as RigidBody's instead of just static colliders. Just using colliders for 
	//Plane's would be more efficient, however, it adds to the complexity of PhysicsEngine class which is un-necissary for
	//this simple simulation.
	bool isKinematic;

	//This is used to stop us from running un-necissary calculations on RigidBody's which are not moving.
	bool isAtRest;

	//This is a count which is used to check how many frames a RigidBody has been still for. Once above a threshold
	//we can consider it to be at rest.
	int restFrames = 0;

	//This variable is used to store the last position of this RigidBody, which is useful for checking if it has moved
	//and therefore whether it needs to be set to rest.
	Vector3 lastDisp;
};

