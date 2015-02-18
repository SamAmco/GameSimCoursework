#pragma once
#include "Renderer.h"

class Sphere
{
public:
	Sphere(Renderer& renderer, float size);

	void Update(float msec);

	~Sphere();
private:
	float size;
	Renderer& renderer;
	Mesh*	mesh;
	Shader* shader;
	RenderObject renderObject;
};

