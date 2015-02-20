#pragma once
#include "Renderer.h"

class Cube
{
public:
	Cube(Renderer& renderer, float size);

	void Update(float sec);

	~Cube();
private:
	float size;
	Renderer& renderer;
	Mesh*	mesh;
	Shader* shader;
	RenderObject renderObject;
};

