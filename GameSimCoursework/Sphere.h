#pragma once
#include "Renderer.h"
#include "RigidBody.h"
#include "PhysicsEngine.h"
#include "SphereCollider.h"

//A Sphere is a type of RigidBody that also stores information relevant to rendering that RigidBody
//through the Renderer.
class Sphere : public RigidBody
{
public:
	Sphere(Renderer& renderer, PhysicsEngine& physicsEngine, Mesh* mesh, Shader* shader, float size,
		Vector3 position = Vector3(),
		Vector3 velocity = Vector3(),
		Vector3 acceleration = Vector3(),
		float mass = 1);

	void Update(float sec);

	~Sphere();

private:
	float size;
	Mesh* mesh;
	Shader* shader;
	RenderObject renderObject;
	SphereCollider sphereCollider;
};

