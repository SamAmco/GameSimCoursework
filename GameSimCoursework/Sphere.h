#pragma once
#include "Renderer.h"
#include "RigidBody.h"
#include "PhysicsEngine.h"


class Sphere
{
public:
	Sphere(Renderer& renderer, PhysicsEngine& physicsEngine, float size);

	void Update(float sec);

	~Sphere();

private:
	float size;
	Renderer& renderer;
	Mesh*	mesh;
	Shader* shader;
	RenderObject renderObject;
	RigidBody rigidBody;
};

