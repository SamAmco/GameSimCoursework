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
	for each (RigidBody* r1 in rigidBodys)
	{
		for each (RigidBody* r2 in rigidBodys)
		{
			if (r1 == r2)
				break;

			PhysVector3 collisionPoint;

			if (r1->sphereCollider.Collides(collisionPoint, r2->sphereCollider, r1->position, r2->position))
			{
				cout << "Sphere sphere collision: " << collisionPoint << endl;
			}
		}
	}
}

PhysicsEngine::~PhysicsEngine()
{
}
