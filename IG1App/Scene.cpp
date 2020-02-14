#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
    // Lights
    // Textures

    // Graphics objects (entities) of the scene

	gObjects.push_back(new EjesRGB(400.0));

	
	Poligono* triangulo = new Poligono(3, 150);
	triangulo->changeColor({1,1,0,0});
	gObjects.push_back(triangulo);
	Poligono* circunferencia = new Poligono(200, 150);
	circunferencia->changeColor({ 1,0,0.85,0 });
	gObjects.push_back(circunferencia);
	/*
	Sierpinsky* s = new Sierpinsky(1000,200);
	gObjects.push_back(s);	
	TrianguloRGB* tri = new TrianguloRGB(100.0);
	gObjects.push_back(tri);
	
	RectanguloRGB* rect = new RectanguloRGB(100, 200);
	gObjects.push_back(rect);
	*/
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------


