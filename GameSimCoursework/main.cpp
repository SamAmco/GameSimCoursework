#include "Renderer.h"
#include "RenderObject.h"
#include "Cube.h"
#include "Sphere.h"
#include "PhysicsEngine.h"

#pragma comment(lib, "nclgl.lib")

void main(void) 
{
	Window w = Window(900, 700);
	Renderer r(w);
	Vector3 lightCol = Vector3(1, 1, 1);
	Vector3 lightPos = Vector3(20.0f, 20.0f, -10);
	float lightRad = 3000.0f;
	r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	r.SetMainLight(lightCol, lightPos, lightRad);
	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 10), Vector3(0, 0, 0)));
	PhysicsEngine physicsEngine = PhysicsEngine();

	Cube cube = Cube(r, physicsEngine, 3);
	Sphere sphere1 = Sphere(r, physicsEngine, 0.3f, PhysVector3(-1, 0, 0), PhysVector3(2, 1, 1), PhysVector3(0, 0, 0), 1);
	Sphere sphere2 = Sphere(r, physicsEngine, 0.3f, PhysVector3(1, 0, 0), PhysVector3(3, 1, -1), PhysVector3(0, 0, 0), 1);

	while(w.UpdateWindow())
	{
		float sec = w.GetTimer()->GetTimedMS() / 1000.0f;
		physicsEngine.Update(sec);

		cube.Update(sec);
		sphere1.Update(sec);
		sphere2.Update(sec);

		r.UpdateScene(sec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();
	}
}