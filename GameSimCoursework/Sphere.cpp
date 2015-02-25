#include "Sphere.h"

Sphere::Sphere(Renderer& renderer, 
	PhysicsEngine& physicsEngine, 
	Mesh* mesh,
	Shader* shader,
	float size,
	PhysVector3 position,
	PhysVector3 velocity,
	PhysVector3 acceleration,
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
