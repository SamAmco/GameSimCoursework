#include "Cube.h"


Cube::Cube(Renderer& renderer, PhysicsEngine& physicsEngine, float size) :
renderer(renderer), physicsEngine(physicsEngine), size(size)
{
	//Since we only have one cube in the world we can do mesh and shader loading here without a loss of efficiency
	mesh = Mesh::LoadMeshFile("Meshes/cube.obj");
	shader = new Shader("Shaders/BasicVert.glsl", "Shaders/WhiteFrag.glsl", "Shaders/WireframeGeom.glsl");
	renderObject = RenderObject(mesh, shader);
	renderObject.SetModelMatrix(Matrix4::Scale(Vector3(size, size, size)));
	renderer.AddRenderObject(renderObject);

	rigidBodys = vector<RigidBody*>(6);

	for (int i = 0; i < rigidBodys.size(); i++)
	{
		RigidBody* r = new RigidBody();
		rigidBodys[i] = r;
		r->isKinematic = true;
		physicsEngine.AddRigidBody(r);
	}
	//First set the plane normals
	rigidBodys[0]->collider = new PlaneCollider(Vector3(1, 0, 0));
	rigidBodys[1]->collider = new PlaneCollider(Vector3(0, 0, 1));
	rigidBodys[2]->collider = new PlaneCollider(Vector3(-1, 0, 0));
	rigidBodys[3]->collider = new PlaneCollider(Vector3(0, 0, -1));
	rigidBodys[4]->collider = new PlaneCollider(Vector3(0, -1, 0));
	rigidBodys[5]->collider = new PlaneCollider(Vector3(0, 1, 0));
	//Then the plane positions
	rigidBodys[0]->collider->translation = Vector3(-size, 0, 0);
	rigidBodys[1]->collider->translation = Vector3(0, 0, -size);
	rigidBodys[2]->collider->translation = Vector3(size, 0, 0);
	rigidBodys[3]->collider->translation = Vector3(0, 0, size);
	rigidBodys[4]->collider->translation = Vector3(0, size, 0);
	rigidBodys[5]->collider->translation = Vector3(0, -size, 0);
}

void Cube::Update(float sec)
{
	bool update = false;
	Matrix4 t = renderObject.GetModelMatrix();
	Matrix4 rot;
	if (Keyboard::KeyDown(KeyboardKeys::KEY_L))
	{
		update = true;
		rot = Matrix4::Rotation(80 * sec, Vector3(1, 0, 0));
	}
	if (Keyboard::KeyDown(KeyboardKeys::KEY_K))
	{
		update = true;
		rot = rot * Matrix4::Rotation(-80 * sec, Vector3(0, 0, 1));
	}
	t = rot*t;

	//If a rotation key has been pressed we need to rotate the position and normal of all of the planes,
	//adjust the cubes model matrix to reflect the rotation, and unrest all the spheres in the system.
	//This stops the planes from being able to rotate out from underneath spheres which are at rest leaving them
	//floating in mid air.
	if (update)
	{
		for each (RigidBody* r in rigidBodys)
		{
			PlaneCollider* p = dynamic_cast<PlaneCollider*>(r->collider);
			if (p)
			{
				p->normal = (rot * p->normal).Normalised();
				p->translation = rot * p->translation;
			}
		}
		renderObject.SetModelMatrix(t);
		physicsEngine.UnrestAll();
	}
}


Cube::~Cube()
{
	for each (RigidBody* r in rigidBodys)
	{
		delete r->collider;
		delete r;
	}
	delete shader;
}
