#pragma once
#include "Renderer.h"
#include "RigidBody.h"
#include "PhysicsEngine.h"
#include "PlaneCollider.h"

//Cube defines the behaviour for the cube that contains the spheres
//it is made up of 6 Kinematic RigidBodys with PlaneColliders. It also holds the graphical information
//for rendering the cube
class Cube
{
public:
	Cube(Renderer& renderer, PhysicsEngine& physicsEngine, float size);

	void Update(float sec);

	~Cube();
private:
	float size;
	Renderer& renderer;
	PhysicsEngine& physicsEngine;
	Mesh*	mesh;
	Shader* shader;
	RenderObject renderObject;
	vector<RigidBody*> rigidBodys;
};

