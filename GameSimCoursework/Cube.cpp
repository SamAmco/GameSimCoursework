#include "Cube.h"


Cube::Cube(Renderer& renderer, PhysicsEngine& physicsEngine, float size) :
renderer(renderer), size(size)
{
	mesh = Mesh::LoadMeshFile("cube.obj");
	shader = new Shader("Shaders/BasicVert.glsl", "Shaders/WhiteFrag.glsl", "Shaders/WireframeGeom.glsl");
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

void Cube::Update(float sec)
{
	//renderObject.SetModelMatrix(renderObject.GetModelMatrix() * Matrix4::Rotation(0.1f * msec, Vector3(1, 1, 1)));
}


Cube::~Cube()
{
	delete mesh;
	delete shader;
}
