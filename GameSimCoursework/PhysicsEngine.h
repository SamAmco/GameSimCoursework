#pragma once
#include <vector>
#include "RigidBody.h"
#include <algorithm>
#include "PhysicsMaths.h"

using namespace std;

//This struct is used for storing pairs of RigidBodys that will need to be checked for 
//collision after running sort and sweep
struct CollisionPair
{
	RigidBody* a;
	RigidBody* b;
};

//The physics engine class stores a vector of RigidBodys which it updates each frame.
//It also defines certain physical rules about the simulation, such as elasticity and gravity
class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void Update(float sec);
	void AddRigidBody(RigidBody* r);
	void UnrestAll();

private:
	vector<RigidBody*> rigidBodys;
	const float elasticity = 0.7f;
	const Vector3 gravity = Vector3(0, -9.81, 0);
	
	void updatePositions(float sec);
	vector<CollisionPair> sortAndSweep();
	static bool compareRigidBodys(const RigidBody* a, const RigidBody* b);
	void collisionDetection(vector<CollisionPair> pairs);
};

