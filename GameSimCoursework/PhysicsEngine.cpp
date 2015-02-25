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
			float penetrationDepth;

			if (rigidBodys[x]->collider->Collides(contactNormal, *(rigidBodys[y]->collider), penetrationDepth))
			{
				PhysVector3 vab = rigidBodys[x]->velocity - rigidBodys[y]->velocity;

				float xInvMass = rigidBodys[x]->isKinematic ? 0 : rigidBodys[x]->inverseMass;
				float yInvMass = rigidBodys[y]->isKinematic ? 0 : rigidBodys[y]->inverseMass;

				float J = (-(1.0f + elasticity) * PhysVector3::dot(vab, contactNormal)) /
					(PhysVector3::dot(contactNormal, contactNormal * (xInvMass + yInvMass)));

				//Projection
				float ratio = xInvMass / (xInvMass + yInvMass);
				Vector3 xPos = rigidBodys[x]->collider->transform.GetPositionVector();
				PhysVector3 xOff = PhysVector3(xPos) - (contactNormal * penetrationDepth * ratio);
				rigidBodys[x]->collider->transform.SetPositionVector(Vector3(xOff.getX(), xOff.getY(), xOff.getZ()));

				Vector3 yPos = rigidBodys[y]->collider->transform.GetPositionVector();
				PhysVector3 yOff = PhysVector3(yPos) + (contactNormal * penetrationDepth * (1.0 - ratio));
				rigidBodys[y]->collider->transform.SetPositionVector(Vector3(yOff.getX(), yOff.getY(), yOff.getZ()));

				//Impulse
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
