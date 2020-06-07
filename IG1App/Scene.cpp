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

	if (mId == 0) {
		Poligono* triangulo = new Poligono(3, 600);
		triangulo->changeColor({ 1,1,0,0 });
		gObjects.push_back(triangulo);
		triangulo->setModelMat(translate(triangulo->modelMat(), dvec3(0.0, 0.0, -90.0)));
		triangulo->setModelMat(rotate(triangulo->modelMat(), radians(180.0), dvec3(0.0, 0.0, 1.0)));

		Poligono* circunferencia = new Poligono(200, 300);
		circunferencia->changeColor({ 1,0,0.85,0 });
		gObjects.push_back(circunferencia);

		Sierpinsky* s = new Sierpinsky(100000, 300);
		gObjects.push_back(s);
		s->changeColor({ 1.0, 1.0, 0.0, 1.0 });

		RectanguloRGB* rect = new RectanguloRGB(1920, 1080);
		gObjects.push_back(rect);
		rect->setModelMat(translate(rect->modelMat(), dvec3(0.0, 0.0, -100.0)));

		TrianguloRGB* triRGB = new TrianguloRGB(100.0);
		gObjects.push_back(triRGB);
		triRGB->setModelMat(translate(triRGB->modelMat(), dvec3(300.0, 0.0, 0.0)));
	}
	else if (mId == 1) {
		for (int i = 0; i < 7; i++) {
			gTextures.push_back(new Texture());
		}
		gTextures[0]->load("../Bmps/baldosaP.bmp");
		gTextures[1]->load("../Bmps/baldosaC.bmp");
		gTextures[2]->load("../Bmps/container.bmp");
		gTextures[3]->load("../Bmps/papelE.bmp");
		gTextures[4]->load("../Bmps/windowV.bmp",127);
		gTextures[5]->load("../Bmps/grass.bmp",glm::u8vec3(0,0,0),0);
		GLdouble l = 70;

		Estrella3D* estr3D = new Estrella3D(l/2, 6, -l/2);
		estr3D->setTexture(gTextures[0]);
		estr3D->setModelMat(translate(estr3D->modelMat(), dvec3(-l / 2, l * 2, -l / 2)));
		gObjects.push_back(estr3D);
		Caja* caj = new Caja(l);
		caj->setTexture(gTextures[2]);
		caj->setTexture2(gTextures[3]);
		gObjects.push_back(caj);
		caj->setModelMat(translate(caj->modelMat(), dvec3(-l/2, l/2, -l / 2)));
		caj->setModelMat2(translate(caj->modelMat2(), dvec3(-l / 2, -l / 2, -l)));
		Suelo* s = new Suelo(l*6, l*6);
		s->setTexture(gTextures[1]);
		gObjects.push_back(s);
		Foto* f = new Foto(l*3, l*2);
		f->setTexture(gTextures[6]);
		f->setModelMat(translate(f->modelMat(), dvec3((l*3)/2, l * 2, 1.0)));
		gObjects.push_back(f);
		Planta* p = new Planta(l*2);
		p->setTexture(gTextures[5]);
		p->setModelMat(translate(p->modelMat(), dvec3(l * 2, l, l * 2)));
		gObjects.push_back(p);
		Cristalera* c = new Cristalera(l*6);
		c->setTexture(gTextures[4]);
		c->setModelMat(translate(c->modelMat(), dvec3(0.0, (l*6)/2, 0.0)));
		gObjects.push_back(c);
	}

}
//-------------------------------------------------------------------------
void Scene::free()
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	for (Texture* el : gTextures)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();
	gTextures.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D); 

}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);  
}
//-------------------------------------------------------------------------

void Scene::update()
{
	for (Abs_Entity* e : gObjects)
	{
	  e->update();
	}
}
void Scene::makeBmp(const std::string& BMP_Name)
{
	Texture* bmpT = new Texture();
	bmpT->loadColorBuffer();
	bmpT->save("../Bmps/"+BMP_Name+".bmp");
	delete bmpT;
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


