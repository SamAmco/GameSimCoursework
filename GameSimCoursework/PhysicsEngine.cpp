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
			//squaring d is more efficient than finding the square root of the sqrMagnitude
			float d = r1->sphereCollider.radius + r2->sphereCollider.radius;
			PhysVector3 norm = r1->position - r2->position;
			if (norm.sqrMagnitude() < d * d)
			{
				float p = (r1->sphereCollider.radius + r2->sphereCollider.radius) - d;
				norm.normalise();
				PhysVector3 colPoint = r1->position - (norm * (r1->sphereCollider.radius - p));
				cout << "Sphere Sphere Collision " << sec << endl;
			}
		}
	}
}

PhysicsEngine::~PhysicsEngine()
{
}
