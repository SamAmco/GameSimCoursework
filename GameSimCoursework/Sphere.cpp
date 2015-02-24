#include "Sphere.h"

Sphere::Sphere(Renderer& renderer, 
	PhysicsEngine& physicsEngine, 
	float size,
	PhysVector3 position,
	PhysVector3 velocity,
	PhysVector3 acceleration,
	float mass) 
	: RigidBody(acceleration, velocity, mass), size(size), sphereCollider(SphereCollider(size))
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

	Matrix4 transform = Matrix4();
	transform.SetPositionVector(Vector3(position.getX(), position.getY(), position.getZ()));
	transform.SetScalingVector(Vector3(size, size, size));
	sphereCollider.transform = transform;
	collider = &sphereCollider;

	renderer.AddRenderObject(renderObject);
	RigidBody* rigidBodyP = this;
	physicsEngine.AddRigidBody(rigidBodyP);
}

void Sphere::Update(float sec)
{
	renderObject.SetModelMatrix(collider->transform);
}


Sphere::~Sphere()
{
}
