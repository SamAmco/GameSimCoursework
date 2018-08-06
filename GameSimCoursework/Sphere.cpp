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
	//Create a RenderObject and add it to the Renderer
	renderObject = RenderObject(mesh, shader);

	Matrix4 transform = Matrix4();
	transform.SetPositionVector(position);
	transform.SetScalingVector(Vector3(size, size, size));
	renderObject.SetModelMatrix(transform);
	renderer.AddRenderObject(renderObject);

	//Add the relevant physics objects to the simulation
	sphereCollider.translation = position;
	collider = &sphereCollider;
	RigidBody* rigidBodyP = this;
	physicsEngine.AddRigidBody(rigidBodyP);
}

//Simply adjust the RenderObject to reflect the corresponding physics object.
void Sphere::Update(float sec)
{
	renderObject.SetModelMatrix(Matrix4::Translation(collider->translation) * Matrix4::Scale(Vector3(size, size, size)));
}


Sphere::~Sphere()
{
}
