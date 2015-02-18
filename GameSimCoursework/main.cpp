#include "Renderer.h"
#include "RenderObject.h"
#include "Cube.h"

#pragma comment(lib, "nclgl.lib")

void main(void) 
{
	Window w = Window(800, 600);
	Renderer r(w);
	r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));

	Cube cube = Cube(r, 1);

	while(w.UpdateWindow()) 
	{
		float msec = w.GetTimer()->GetTimedMS();

		cube.Update(msec);

		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();
	}
}