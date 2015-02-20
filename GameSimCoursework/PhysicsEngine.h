#pragma once
#include <vector>
#include "RigidBody.h"

using namespace std;

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void Update(float sec);
	void AddRigidBody(RigidBody* r);

private:
	vector<RigidBody*> rigidBodys;
	void updatePositions(float sec);
	void collisionDetection(float sec);
};

