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
		r->collider->Project(PhysVector3(1,0,0));
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
	//write custom comparer for mins
	//std::sort the rigidBodys
	//sweep (sort of like n^2 loop)
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
		if (!r->isKinematic)
			PhysicsMaths::semiImplicitEuler(*r, gravity, sec);
	}
}

void PhysicsEngine::collisionDetection(vector<CollisionPair> pairs)
{
	//cout << pairs.size() << endl;
	for each (CollisionPair collisionPair in pairs)
	{
		PhysVector3 contactNormal;
		float penetrationDepth;

		if (collisionPair.a->collider->Collides(contactNormal, *(collisionPair.b->collider), penetrationDepth))
		{
			PhysVector3 vab = collisionPair.a->velocity - collisionPair.b->velocity;

			float xInvMass = collisionPair.a->isKinematic ? 0 : collisionPair.a->inverseMass;
			float yInvMass = collisionPair.b->isKinematic ? 0 : collisionPair.b->inverseMass;

			float J = (-(1.0f + elasticity) * PhysVector3::dot(vab, contactNormal)) /
				(PhysVector3::dot(contactNormal, contactNormal * (xInvMass + yInvMass)));

			//Projection
			float ratio = xInvMass / (xInvMass + yInvMass);
			Vector3 xPos = collisionPair.a->collider->transform.GetPositionVector();
			PhysVector3 xOff = PhysVector3(xPos) - (contactNormal * penetrationDepth * ratio);
			collisionPair.a->collider->transform.SetPositionVector(Vector3(xOff.getX(), xOff.getY(), xOff.getZ()));

			Vector3 yPos = collisionPair.b->collider->transform.GetPositionVector();
			PhysVector3 yOff = PhysVector3(yPos) + (contactNormal * penetrationDepth * (1.0 - ratio));
			collisionPair.b->collider->transform.SetPositionVector(Vector3(yOff.getX(), yOff.getY(), yOff.getZ()));

			//Impulse
			collisionPair.a->velocity = collisionPair.a->velocity
				+ (contactNormal * (J * xInvMass));
			collisionPair.b->velocity = collisionPair.b->velocity
				- (contactNormal * (J * yInvMass));
		}
	}
}

PhysicsEngine::~PhysicsEngine()
{
}
