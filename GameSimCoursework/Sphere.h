#pragma once
#include "Renderer.h"
#include "RigidBody.h"
#include "PhysicsEngine.h"
#include "SphereCollider.h"

class Sphere : public RigidBody
{
public:
	Sphere(Renderer& renderer, PhysicsEngine& physicsEngine, Mesh* mesh, Shader* shader, float size,
		PhysVector3 position = PhysVector3::zero(),
		PhysVector3 velocity = PhysVector3::zero(),
		PhysVector3 acceleration = PhysVector3::zero(),
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

