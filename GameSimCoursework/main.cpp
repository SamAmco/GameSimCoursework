#include "Renderer.h"
#include "RenderObject.h"
#include "Cube.h"
#include "Sphere.h"

#pragma comment(lib, "nclgl.lib")

void main(void) 
{
	Window w = Window(800, 600);
	Renderer r(w);
	Vector3 lightCol = Vector3(1, 1, 1);
	Vector3 lightPos = Vector3(20.0f, 20.0f, -10);
	float lightRad = 3000.0f;
	r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	r.SetMainLight(lightCol, lightPos, lightRad);
	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));

	Cube cube = Cube(r, 2);
	Sphere sphere = Sphere(r, 1);

	while(w.UpdateWindow()) 
	{
		float msec = w.GetTimer()->GetTimedMS();

		//Spin the light
		//Matrix4 p = Matrix4();
		//p.ToIdentity();
		//p.SetPositionVector(lightPos);
		//lightPos = (Matrix4::Rotation(0.1f * msec, Vector3(0, 1, 0)) * p).GetPositionVector();
		//r.SetMainLight(lightCol, lightPos, lightRad);

		cube.Update(msec);
		sphere.Update(msec);

		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();
	}
}