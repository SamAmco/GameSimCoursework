#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
	rigidBodys = vector<RigidBody*>();
}

//This is the function that gets called by main
void PhysicsEngine::Update(float sec)
{
	updatePositions(sec);
	vector<CollisionPair> pairs = sortAndSweep();
	collisionDetection(pairs);
}

//This is the function that Cube and Sphere use to add their RigidBody's to the 
//simulation
void PhysicsEngine::AddRigidBody(RigidBody* r)
{
	rigidBodys.push_back(r);
}

//Set all RigidBodys to not be at rest. Useful when the cube rotates to prevent anomalous 
//behaviour 
void PhysicsEngine::UnrestAll()
{
	for each (RigidBody* r in rigidBodys)
	{
		r->isAtRest = false;
	}
}

//Broad Phase Collision detection method
vector<CollisionPair> PhysicsEngine::sortAndSweep()
{
	//First project all rigid bodys against an axis to get their min and max values on that axis
	vector<CollisionPair> pairs = vector<CollisionPair>(); 
	for each (RigidBody* r in rigidBodys)
	{
		r->collider->Project(Vector3(1,0,0));
	}
	//Now sort them by their minimum projection values. Ideally here we would use insertion sort,
	//since the order does not change much from one frame to the next. This would take advantage of temporal coherence, 
	//but for the sake of this simulation it is not a noticable performance increase
	std::sort(rigidBodys.begin(), rigidBodys.end(), compareRigidBodys);
	
	//Now go through each RigidBody and add a collision pair to the list for every possible other RigidBody it could
	//be colliding with. That is every object who's min projection is smaller than this objects max projection on the 
	//same axis.
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

//This function is used to sort RigidBody's by their min projection value for the sake of sort and sweep.
bool PhysicsEngine::compareRigidBodys(const RigidBody* a, const RigidBody* b)
{
	return a->collider->projection.min < b->collider->projection.min;
}

//Apply semi implicit Euler to every RigidBody that is not kinematic or at rest
void PhysicsEngine::updatePositions(float sec)
{
	for each (RigidBody* r in rigidBodys)
	{
		if (!(r->isKinematic || r->isAtRest))
			PhysicsMaths::semiImplicitEuler(*r, gravity, sec);
	}
}

//Check and resolve collisions between every pair of possibly colliding objects in the simulation
void PhysicsEngine::collisionDetection(vector<CollisionPair> pairs)
{
	for each (CollisionPair collisionPair in pairs)
	{
		//These values are passed by reference to the collides function and will store the 
		//relevant information for resolving the collision if a collision takes place.
		Vector3 contactNormal;
		float penetrationDepth;

		if (collisionPair.a->collider->Collides(contactNormal, *(collisionPair.b->collider), penetrationDepth))
		{
			//THE RigidBody's ARE COLLIDING
			Vector3 vab = collisionPair.a->velocity - collisionPair.b->velocity;

			//If either are kinematic then they will gain no velocity and not be offset at all as a 
			//result of the collision. So we can store an inverse mass of 0 for them to ensure this.
			float xInvMass = collisionPair.a->isKinematic ? 0 : collisionPair.a->inverseMass;
			float yInvMass = collisionPair.b->isKinematic ? 0 : collisionPair.b->inverseMass;

			//Calculate the Impulse used to affect the velocitys of the objects
			float J = (-(1.0f + elasticity) * Vector3::Dot(vab, contactNormal)) /
				(Vector3::Dot(contactNormal, contactNormal * (xInvMass + yInvMass)));

			//Projection method. This is used to move the objects away from each other
			//to account for penetration. We move each object away from the other along the
			//normal of the collision an amount proportional to it's mass compared with the other
			float ratio = xInvMass / (xInvMass + yInvMass);
			Vector3 xPos = collisionPair.a->collider->translation;
			Vector3 xOff = xPos - (contactNormal * penetrationDepth * ratio);
			collisionPair.a->collider->translation = xOff;

			Vector3 yPos = collisionPair.b->collider->translation;
			Vector3 yOff = yPos + (contactNormal * penetrationDepth * (1.0 - ratio));
			collisionPair.b->collider->translation = yOff;

			//Impulse method. This is used to make the RigidBody's gain a velocity away from 
			//each other.
			Vector3 aVel = (contactNormal * (J * xInvMass));
			Vector3 bVel = (contactNormal * (J * yInvMass));
			collisionPair.a->velocity += aVel;
			collisionPair.b->velocity -= bVel;

			//We only need to unrest the bodys if they gained a velocity from the collision that 
			//exceeds a certain threshold. This stops RigidBody's from being unrested when they are
			//simply in contact with the floor. 
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
