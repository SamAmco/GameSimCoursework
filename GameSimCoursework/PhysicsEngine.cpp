#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
	rigidBodys = vector<RigidBody*>();
}

void PhysicsEngine::Update(float sec)
{
	updatePositions(sec);
	vector<CollisionPair> pairs = sortAndSweep();
	collisionDetection(pairs);
}

void PhysicsEngine::AddRigidBody(RigidBody* r)
{
	rigidBodys.push_back(r);
}

vector<CollisionPair> PhysicsEngine::sortAndSweep()
{
	vector<CollisionPair> pairs = vector<CollisionPair>(); 
	for each (RigidBody* r in rigidBodys)
	{
		r->collider->Project(Vector3(1,0,0));
	}
	std::sort(rigidBodys.begin(), rigidBodys.end(), compareRigidBodys);
	for (int x = 0; x < rigidBodys.size(); x++)
	{
		for (int y = x + 1; y < rigidBodys.size(); y++)
		{
			if (rigidBodys[x]->collider->projection.max < rigidBodys[y]->collider->projection.min)
				break;
			else
			{
				CollisionPair p;
				p.a = rigidBodys[x];
				p.b = rigidBodys[y];
				pairs.push_back(p);
			}
		}
	}
	return pairs;
}

bool PhysicsEngine::compareRigidBodys(const RigidBody* a, const RigidBody* b)
{
	return a->collider->projection.min < b->collider->projection.min;
}


void PhysicsEngine::updatePositions(float sec)
{
	for each (RigidBody* r in rigidBodys)
	{
		if (!(r->isKinematic || r->isAtRest))
			PhysicsMaths::semiImplicitEuler(*r, gravity, sec);
	}
}

void PhysicsEngine::collisionDetection(vector<CollisionPair> pairs)
{
	for each (CollisionPair collisionPair in pairs)
	{
		Vector3 contactNormal;
		float penetrationDepth;

		if (collisionPair.a->collider->Collides(contactNormal, *(collisionPair.b->collider), penetrationDepth))
		{
			Vector3 vab = collisionPair.a->velocity - collisionPair.b->velocity;

			float xInvMass = collisionPair.a->isKinematic ? 0 : collisionPair.a->inverseMass;
			float yInvMass = collisionPair.b->isKinematic ? 0 : collisionPair.b->inverseMass;

			float J = (-(1.0f + elasticity) * Vector3::Dot(vab, contactNormal)) /
				(Vector3::Dot(contactNormal, contactNormal * (xInvMass + yInvMass)));

			//Projection
			float ratio = xInvMass / (xInvMass + yInvMass);
			Vector3 xPos = collisionPair.a->collider->translation;
			Vector3 xOff = xPos - (contactNormal * penetrationDepth * ratio);
			collisionPair.a->collider->translation = xOff;

			Vector3 yPos = collisionPair.b->collider->translation;
			Vector3 yOff = yPos + (contactNormal * penetrationDepth * (1.0 - ratio));
			collisionPair.b->collider->translation = yOff;

			//Impulse
			Vector3 aVel = (contactNormal * (J * xInvMass));
			Vector3 bVel = (contactNormal * (J * yInvMass));
			collisionPair.a->velocity += aVel;
			collisionPair.b->velocity -= bVel;

			if (aVel.sqrLength() > REST_THRESHOLD)
				collisionPair.a->isAtRest = false;
			if (bVel.sqrLength() > REST_THRESHOLD)
				collisionPair.b->isAtRest = false;
		}
	}
}

PhysicsEngine::~PhysicsEngine()
{
}
