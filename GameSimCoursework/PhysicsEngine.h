#pragma once
#include <vector>
#include "RigidBody.h"

using namespace std;

struct CollisionPair
{
	RigidBody* a;
	RigidBody* b;
};

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void Update(float sec);
	void AddRigidBody(RigidBody* r);

private:
	vector<RigidBody*> rigidBodys;
	const float elasticity = 0.7f;
	const PhysVector3 gravity = PhysVector3(0, -9.81, 0);
	
	void updatePositions(float sec);
	vector<CollisionPair> sortAndSweep();
	void collisionDetection(vector<CollisionPair> pairs);
};

