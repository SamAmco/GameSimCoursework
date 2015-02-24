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
		if (!r->isKinematic)
			PhysicsMaths::semiImplicitEuler(*r, sec);
	}
}

void PhysicsEngine::collisionDetection(float sec)
{

	for (int x = 0; x < rigidBodys.size(); x++)
	{
		for (int y = x + 1; y < rigidBodys.size(); y++)
		{
			PhysVector3 contactNormal;

			if (rigidBodys[x]->collider->Collides(contactNormal, *(rigidBodys[y]->collider)))
			{
				cout << "collision: " << contactNormal << endl;
				PhysVector3 vab = rigidBodys[x]->velocity + rigidBodys[y]->velocity;

				float xInvMass = rigidBodys[x]->isKinematic ? 0 : rigidBodys[x]->inverseMass;
				float yInvMass = rigidBodys[y]->isKinematic ? 0 : rigidBodys[y]->inverseMass;

				float J = PhysVector3::dot(vab * -(1 + elasticity), contactNormal) /
					(PhysVector3::dot(contactNormal, contactNormal) * (xInvMass + yInvMass));

				rigidBodys[x]->velocity = rigidBodys[x]->velocity 
					+ (contactNormal * (J * xInvMass));
				rigidBodys[y]->velocity = rigidBodys[y]->velocity
					- (contactNormal * (J * yInvMass));
			}
		}
	}
}

PhysicsEngine::~PhysicsEngine()
{
}
