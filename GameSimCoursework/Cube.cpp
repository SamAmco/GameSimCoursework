#include "Cube.h"


Cube::Cube(Renderer& renderer, PhysicsEngine& physicsEngine, float size) :
renderer(renderer), size(size)
{
	mesh = Mesh::LoadMeshFile("cube.obj");
	shader = new Shader("Shaders/BasicVert.glsl", "Shaders/WhiteFrag.glsl", "Shaders/WireframeGeom.glsl");
	transform = Matrix4::Scale(Vector3(size, size, size));
	if (shader->UsingDefaultShader())
	{
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}
	renderObject = RenderObject(mesh, shader);
	renderObject.SetModelMatrix(transform);
	renderer.AddRenderObject(renderObject);

	rigidBodys = vector<RigidBody*>(6);

	for (int i = 0; i < rigidBodys.size(); i++)
	{
		RigidBody* r = new RigidBody();
		rigidBodys[i] = r;
		r->isKinematic = true;
		physicsEngine.AddRigidBody(r);
	}
	rigidBodys[0]->collider = new PlaneCollider(PhysVector3(1, 0, 0));
	rigidBodys[1]->collider = new PlaneCollider(PhysVector3(0, 0, 1));
	rigidBodys[2]->collider = new PlaneCollider(PhysVector3(-1, 0, 0));
	rigidBodys[3]->collider = new PlaneCollider(PhysVector3(0, 0, -1));
	rigidBodys[4]->collider = new PlaneCollider(PhysVector3(0, -1, 0));
	rigidBodys[5]->collider = new PlaneCollider(PhysVector3(0, 1, 0));
	rigidBodys[0]->collider->transform = Matrix4::Translation(Vector3(-size, 0, 0));
	rigidBodys[1]->collider->transform = Matrix4::Translation(Vector3(0, 0, -size));
	rigidBodys[2]->collider->transform = Matrix4::Translation(Vector3(size, 0, 0));
	rigidBodys[3]->collider->transform = Matrix4::Translation(Vector3(0, 0, size));
	rigidBodys[4]->collider->transform = Matrix4::Translation(Vector3(0, size, 0));
	rigidBodys[5]->collider->transform = Matrix4::Translation(Vector3(0, -size, 0));

	Update(0);
}

void Cube::Update(float sec)
{
	bool update = false;
	Matrix4 t = renderObject.GetModelMatrix();
	Matrix4 rot;
	if (Keyboard::KeyDown(KeyboardKeys::KEY_L))
	{
		update = true;
		rot = Matrix4::Rotation(80 * sec, Vector3(0, 0, 1));
	}
	if (Keyboard::KeyDown(KeyboardKeys::KEY_K))
	{
		update = true;
		rot = rot * Matrix4::Rotation(-80 * sec, Vector3(0, 0, 1));
	}
	if (Keyboard::KeyDown(KeyboardKeys::KEY_U))
	{
		update = true;
		rot = rot * Matrix4::Rotation(80 * sec, Vector3(1, 0, 0));
	}
	if (Keyboard::KeyDown(KeyboardKeys::KEY_J))
	{
		update = true;
		rot = rot * Matrix4::Rotation(-80 * sec, Vector3(1, 0, 0));
	}
	t = rot*t;

	if (update)
	{
		for each (RigidBody* r in rigidBodys)
		{
			PlaneCollider* p = dynamic_cast<PlaneCollider*>(r->collider);
			if (p)
			{
				//We is a plane, do shit fam
				p->normal = PhysVector3(rot * Vector3(p->normal.getX(), p->normal.getY(), p->normal.getZ())).normalise();
				p->transform = rot * p->transform;
			}
		}
		/*rigidBodys[0]->collider->transform = t * Matrix4::Translation(Vector3(-size, 0, 0));
		rigidBodys[1]->collider->transform = t * Matrix4::Translation(Vector3(0, 0, -size));
		rigidBodys[2]->collider->transform = t * Matrix4::Translation(Vector3(size, 0, 0)) ;
		rigidBodys[3]->collider->transform = t * Matrix4::Translation(Vector3(0, 0, size)) ;
		rigidBodys[4]->collider->transform = t * Matrix4::Translation(Vector3(0, size, 0)) ;
		rigidBodys[5]->collider->transform = t * Matrix4::Translation(Vector3(0, -size, 0)); */
		renderObject.SetModelMatrix(t);
	}
}


Cube::~Cube()
{
	delete mesh;
	delete shader;
	for each (RigidBody* r in rigidBodys)
	{
		delete r;
	}
}
