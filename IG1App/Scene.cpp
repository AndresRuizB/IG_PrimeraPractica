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

	textFoto = new Texture();
	textFoto->loadColorBuffer();

	Texture* baldP = new Texture(), * baldC = new Texture(), * containertxt = new Texture(), * papelC = new Texture()
		, * windowC = new Texture();
	baldP->load("../Bmps/baldosaP.bmp");
	gTextures.push_back(baldP);
	baldC->load("../Bmps/baldosaC.bmp");
	gTextures.push_back(baldC);
	containertxt->load("../Bmps/container.bmp");
	gTextures.push_back(containertxt);
	papelC->load("../Bmps/papelC.bmp");
	gTextures.push_back(papelC);
	windowC->load("../Bmps/windowC.bmp", 150);
	gTextures.push_back(windowC);	//4

	// Graphics objects (entities) of the scene

	gObjects.push_back(new EjesRGB(400.0));
	if (mId == 0) {
		//AnilloCuadrado* anilloC = new AnilloCuadrado();
		//gObjects.push_back(anilloC);

		EntityWithIndexMesh* cuboTapas = new EntityWithIndexMesh();
		gObjects.push_back(cuboTapas);

	}
	else if (mId == 1) {

		Sphere* cabeza = new Sphere(200);
		cabeza->setQuadricObjColor({ 1.0, 0.5, 0.0});
		gObjects.push_back(cabeza);

		Disk* halo = new Disk(130, 200);
		halo->setQuadricObjColor({ 0.0, 0.5, 1.0 });
		glm::dmat4 mAux = halo->modelMat(); 
		mAux = translate(mAux, dvec3(0, 150, 0)); 
		mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0, 0)); 
		halo->setModelMat(mAux);
		gObjects.push_back(halo);

		Cylinder* ojo1 = new Cylinder(20,0,40);
		ojo1->setQuadricObjColor({ 1.0, 0.0, 1.0 });
		mAux = ojo1->modelMat();
		mAux = translate(mAux, dvec3(-80, 80, 170));
		ojo1->setModelMat(mAux);
		gObjects.push_back(ojo1);

		Cylinder* ojo2 = new Cylinder(20, 0, 40);
		ojo2->setQuadricObjColor({ 0.5, 0.2, 1.0 });
		mAux = ojo2->modelMat();
		mAux = translate(mAux, dvec3(80, 80, 170));
		ojo2->setModelMat(mAux);
		gObjects.push_back(ojo2);

		
		PartialDisk* barba = new PartialDisk(300, 320, 90, 100);
		barba->setQuadricObjColor({ 0.1, 0.9, 0.6 });
		mAux = barba->modelMat();
		mAux = translate(mAux, dvec3(-50, 200, 185));
		mAux = rotate(mAux, radians(-90.0), dvec3(0, 0.0, 1.0));
		barba->setModelMat(mAux);
		gObjects.push_back(barba);



	}else if (mId == 2) {

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
	else if (mId == 3) {

		Estrella3D* estrella = new Estrella3D(300, 100, 5, 200);
		gObjects.push_back(estrella);

		Caja* caja = new Caja(100);
		caja->setModelMat(translate(caja->modelMat(), dvec3(400.0, 0.0, 0.0)));
		gObjects.push_back(caja);

	}
	else if (mId == 4)
	{
		Estrella3DText* estrellaText = new Estrella3DText(100, 50, 5, 100);
		estrellaText->setTexture(gTextures[0]);
		estrellaText->setModelMat(translate(estrellaText->modelMat(), dvec3(100.0, 300.0, 100.0)));
		gObjects.push_back(estrellaText);

		CajaText* cajaTxt = new CajaText(200);
		cajaTxt->setTexture(gTextures[2]);
		cajaTxt->setTextureInside(gTextures[3]);
		gObjects.push_back(cajaTxt);

		Suelo* suelo = new Suelo(600, 600, 4, 4);
		suelo->setTexture(gTextures[1]);
		gObjects.push_back(suelo);

		Foto* foton = new Foto(200, 300);
		foton->setTexture(textFoto);
		foton->setModelMat(rotate(foton->modelMat(), radians(-90.0), dvec3(1.0, 0.0, 0.0)));
		foton->setModelMat(translate(foton->modelMat(), dvec3(-130.0, 0.0, 1.0)));
		gObjects.push_back(foton);

		Cristalera* cristalera = new Cristalera(600);
		cristalera->setModelMat(translate(cristalera->modelMat(), dvec3(-300.0, 0.0, -300.0)));
		cristalera->setTexture(gTextures[4]);
		gObjects.push_back(cristalera);
	}

}

//-------------------------------------------------------------------------
void Scene::free()
{ // release memory and resources   

	delete textFoto;

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}

	for (Texture* el : gTextures)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL()
{
	// OpenGL basic setting

	if (mId == 0) glClearColor(0.7, 0.8, 0.9, 1.0);
	else glClearColor(1.0, 1.0, 1.0, 1.0);// background color (alpha=1 -> opaque)

	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  // disable textures

}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);  // disable textures
}
//-------------------------------------------------------------------------
void Scene::setState(int id)
{
	Scene::mId = id;
}

//-------------------------------------------------------------------------

void Scene::saveCapture()
{
	Texture *temp = new Texture();
	temp->loadColorBuffer();
	temp->save("name.bmp");
}
//-------------------------------------------------------------------------

void Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
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
	sceneDirLight(cam);
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
		el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------


