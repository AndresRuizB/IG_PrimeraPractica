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

	Poligono* triangulo = new Poligono(3,600);
	triangulo->changeColor({ 1,1,0,0 });
	gObjects.push_back(triangulo);
	triangulo->setModelMat(translate(triangulo->modelMat(), dvec3(0.0, 0.0, -90.0)));
	triangulo->setModelMat(rotate(triangulo->modelMat(),radians(180.0), dvec3(0.0, 0.0, 1.0)));

	Poligono* circunferencia = new Poligono(200, 300);
	circunferencia->changeColor({ 1,0,0.85,0 });
	gObjects.push_back(circunferencia);

	Sierpinsky* s = new Sierpinsky(100000, 300);
	gObjects.push_back(s);
	s->changeColor({ 1.0, 1.0, 0.0, 1.0 });
	
	RectanguloRGB* rect = new RectanguloRGB(1920, 1080);
	gObjects.push_back(rect);
	rect->setModelMat(translate(rect->modelMat(), dvec3(0.0,0.0,-100.0)));

	TrianguloRGB* triRGB = new TrianguloRGB(100.0);
	gObjects.push_back(triRGB);
	triRGB->setModelMat(translate(triRGB->modelMat(), dvec3(300.0, 0.0, 0.0)));

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

void Scene::update()
{
	for (Abs_Entity* e : gObjects)
	{
	  e->update();
	}
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


