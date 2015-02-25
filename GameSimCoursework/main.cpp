#include "Renderer.h"
#include "RenderObject.h"
#include "Cube.h"
#include "Sphere.h"
#include "PhysicsEngine.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#pragma comment(lib, "nclgl.lib")

static Sphere* generateRandomSphere(Renderer& renderer, PhysicsEngine& physicsEngine, Mesh* mesh, Shader* shader)
{

	return new Sphere(renderer, physicsEngine, mesh, shader, max((float)(rand() % 100) / 150.0f, 0.5f),
		PhysVector3::zero(),
		PhysVector3((float)(rand() % 100) / 25.0f, (float)(rand() % 100) / 25.0f, (float)(rand() % 100) / 25.0f),
		PhysVector3::zero(),
		max((float)(rand() % 100) / 25.0f, 1));
}

void main(void) 
{
	Window w = Window(900, 700);
	Renderer renderer(w);
	Vector3 lightCol = Vector3(1, 1, 1);
	Vector3 lightPos = Vector3(20.0f, 20.0f, -10);
	float lightRad = 3000.0f;
	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.SetMainLight(lightCol, lightPos, lightRad);
	renderer.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 10), Vector3(0, 0, 0)));
	PhysicsEngine physicsEngine = PhysicsEngine();

	Cube cube = Cube(renderer, physicsEngine, 3);
	Mesh* mesh = Mesh::LoadMeshFile("sphere.obj", Vector4(0.75, 0.75, 0.75, 1));
	Shader* shader = new Shader("Shaders/PhongColVert.glsl", "Shaders/PhongColFrag.glsl");

	srand(time(NULL));
	rand();

	vector<Sphere*> spheres = vector<Sphere*>();

	float timeCount = 0;
	int numSpheresToGen = 1;
	float timeBetweenSpheres = 0.1f;
	while(w.UpdateWindow())
	{
		float sec = w.GetTimer()->GetTimedMS() / 1000.0f;
		physicsEngine.Update(sec);

		timeCount += sec;
		if (timeCount >= timeBetweenSpheres && spheres.size() < numSpheresToGen)
		{
			spheres.push_back(generateRandomSphere(renderer, physicsEngine, mesh, shader));
			timeCount = 0;
		}

		bool applyUpwardForce = false;
		if (Keyboard::KeyTriggered(KeyboardKeys::KEY_F))
			applyUpwardForce = true;

		for each (Sphere* s in spheres)
		{
			if (applyUpwardForce)
				s->ApplyMomentum(PhysVector3(0, 10, 0));

			s->Update(sec);
		}

		cube.Update(sec);

		renderer.UpdateScene(sec);
		renderer.ClearBuffers();
		renderer.RenderScene();
		renderer.SwapBuffers();
	}

	for each (Sphere* s in spheres)
		delete s;
}