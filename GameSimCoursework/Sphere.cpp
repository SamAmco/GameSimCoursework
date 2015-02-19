#include "Sphere.h"


Sphere::Sphere(Renderer& renderer, float size) :
renderer(renderer), size(size)
{
	mesh = Mesh::LoadMeshFile("sphere.obj", Vector4(0.75, 0.75, 0.75, 1));
	shader = new Shader("Shaders/PhongColVert.glsl", "Shaders/PhongColFrag.glsl");
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

void Sphere::Update(float msec)
{
}


Sphere::~Sphere()
{
}
