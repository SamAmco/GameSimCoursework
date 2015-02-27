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
	float size = fmax((float)(rand() % 100) / 150.0f, 0.4f);
	float mass = fmax((float)(rand() % 100) / 25.0f, 1);
	return new Sphere(renderer, physicsEngine, mesh, shader, size,
		Vector3(),
		Vector3((float)(rand() % 100) / 25.0f, (float)(rand() % 100) / 25.0f, (float)(rand() % 100) / 25.0f),
		Vector3(),
		mass);
}

//THE ENTRY POINT FOR THE PROGRAM
void main(void) 
{
	//Initialize the environment
	Window w = Window(900, 700);
	Renderer renderer(w);
	Vector3 lightCol = Vector3(1, 1, 1);
	Vector3 lightPos = Vector3(20.0f, 20.0f, -10);
	float lightRad = 3000.0f;
	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.SetMainLight(lightCol, lightPos, lightRad);
	renderer.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 10), Vector3(0, 0, 0)));
	srand(time(NULL));
	PhysicsEngine physicsEngine = PhysicsEngine();

	//these are only loaded once here so that we can generate new spheres quickly without causing long frame times
	//in the simulation, and therefore glitches in the physics.
	Cube cube = Cube(renderer, physicsEngine, 3);
	Mesh* mesh = Mesh::LoadMeshFile("sphere.obj", Vector4(0.75, 0.75, 0.75, 1));
	Shader* shader = new Shader("Shaders/PhongColVert.glsl", "Shaders/PhongColFrag.glsl");

	vector<Sphere*> spheres = vector<Sphere*>();

	float timeCount = 0;
	//These can be changed to modify the initialization of the scene
	int numSpheresToGen = 15;
	float timeBetweenSpheres = 0.2f;
	
	while(w.UpdateWindow())
	{
		float sec = w.GetTimer()->GetTimedMS() / 1000.0f;
		//Update the physics engine
		physicsEngine.Update(sec);

		//Add in more sphere's if we need them
		timeCount += sec;
		if (timeCount >= timeBetweenSpheres && spheres.size() < numSpheresToGen)
		{
			spheres.push_back(generateRandomSphere(renderer, physicsEngine, mesh, shader));
			timeCount = 0;
		}

		//Apply an upward force to all spheres if the F key is pressed
		bool applyUpwardForce = false;
		if (Keyboard::KeyTriggered(KeyboardKeys::KEY_F))
			applyUpwardForce = true;

		//Update our spheres
		for each (Sphere* s in spheres)
		{
			if (applyUpwardForce)
				s->ApplyMomentum(Vector3(0, 10, 0));

			s->Update(sec);
		}

		//Update our cube
		cube.Update(sec);

		//Update the renderer and handle frame buffers
		renderer.UpdateScene(sec);
		renderer.ClearBuffers();
		renderer.RenderScene();
		renderer.SwapBuffers();
	}

	for each (Sphere* s in spheres)
		delete s;
	delete shader;
}