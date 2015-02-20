#include "PhysicsEngine.h"
#include "PhysicsMaths.h"


PhysicsEngine::PhysicsEngine()
{
	rigidBodys = vector<RigidBody*>();
}

void PhysicsEngine::Update(float sec)
{
	updatePositions(sec);
	collisionDetection(sec);
}

void PhysicsEngine::AddRigidBody(RigidBody* r)
{
	rigidBodys.push_back(r);
}

void PhysicsEngine::updatePositions(float sec)
{
	for each (RigidBody* r in rigidBodys)
	{
		PhysicsMaths::semiImplicitEuler(r->velocity, r->acceleration, r->position, sec);
	}
}

void PhysicsEngine::collisionDetection(float sec)
{

}

PhysicsEngine::~PhysicsEngine()
{
}
