#include "Cube.h"


Cube::Cube(Renderer& renderer, float size) :
renderer(renderer), size(size)
{
	mesh = Mesh::LoadMeshFile("cube.asciimesh");
	shader = new Shader("basicvert.glsl", "basicFrag.glsl");
	if (shader->UsingDefaultShader())
	{
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}
	renderObject = RenderObject(mesh, shader);
	renderObject.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(size, size, size)));
	renderer.AddRenderObject(renderObject);
}

void Cube::Update(float msec)
{
	renderObject.SetModelMatrix(renderObject.GetModelMatrix() * Matrix4::Rotation(0.1f * msec, Vector3(0, 0, 1)));
}


Cube::~Cube()
{
	delete mesh;
	delete shader;
}
