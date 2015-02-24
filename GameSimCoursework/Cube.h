#pragma once
#include "Renderer.h"
#include "RigidBody.h"
#include "PhysicsEngine.h"

class Cube
{
public:
	Cube(Renderer& renderer, PhysicsEngine& physicsEngine, float size);

	void Update(float sec);

	~Cube();
private:
	float size;
	Renderer& renderer;
	Mesh*	mesh;
	Shader* shader;
	RenderObject renderObject;
	RigidBody* rigidBodys;
};

