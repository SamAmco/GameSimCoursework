#include "Sphere.h"

Sphere::Sphere(Renderer& renderer, 
	PhysicsEngine& physicsEngine, 
	Mesh* mesh,
	Shader* shader,
	float size,
	Vector3 position,
	Vector3 velocity,
	Vector3 acceleration,
	float mass) 
	: RigidBody(acceleration, velocity, mass), mesh(mesh), shader(shader), size(size), sphereCollider(SphereCollider(size))
{
	if (shader->UsingDefaultShader())
	{
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}
	renderObject = RenderObject(mesh, shader);

	Matrix4 transform = Matrix4();
	transform.SetPositionVector(position);
	transform.SetScalingVector(Vector3(size, size, size));
	sphereCollider.translation = position;
	collider = &sphereCollider;

	renderer.AddRenderObject(renderObject);
	RigidBody* rigidBodyP = this;
	physicsEngine.AddRigidBody(rigidBodyP);
}

void Sphere::Update(float sec)
{
	renderObject.SetModelMatrix(Matrix4::Translation(collider->translation) * Matrix4::Scale(Vector3(size, size, size)));
}


Sphere::~Sphere()
{
}
