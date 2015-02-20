#include "Sphere.h"


Sphere::Sphere(Renderer& renderer, PhysicsEngine& physicsEngine, float size) :
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

	rigidBody = RigidBody();
	rigidBody.position = PhysVector3(0, 0, -10);
	rigidBody.velocity = PhysVector3(0,0,0);
	rigidBody.acceleration = PhysVector3(1,0,0);

	renderer.AddRenderObject(renderObject);
	RigidBody* rigidBodyP = &rigidBody;
	physicsEngine.AddRigidBody(rigidBodyP);
}

void Sphere::Update(float sec)
{
	renderObject.SetModelMatrix(Matrix4::Translation(
		Vector3(rigidBody.position.getX(), rigidBody.position.getY(), rigidBody.position.getZ()))
		* Matrix4::Scale(Vector3(size, size, size)));
}


Sphere::~Sphere()
{
}
