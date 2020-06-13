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
	setLights();
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
		Grid* g = new Grid(200, 10);
		g->changeColor(dvec4(0, 0, 1, 1));
		g->setTexture(gTextures[0]);
		gObjects.push_back(g);
	}
	if (mId == 1) {
		glm::dmat4 mAux;
		//AnilloCuadrado* anilloC = new AnilloCuadrado();
		//gObjects.push_back(anilloC);

		//Cubo* cuboTapas = new Cubo(100);
		//gObjects.push_back(cuboTapas);

		CompoundEntity* helices = new CompoundEntity();
		Cylinder* c1 = new Cylinder(20,10,60);
		c1->setQuadricObjColor(fvec3(0, 0, 1));
		mAux = c1->modelMat();
		mAux = translate(mAux, dvec3(0, 0, 110));
		mAux = rotate(mAux, radians(90.0), dvec3(0, 1, 0));
		c1->setModelMat(mAux);
		helices->addEntity(c1);
		Cylinder* c2 = new Cylinder(20, 10, 60);
		c2->setQuadricObjColor(fvec3(0,0,1));
		mAux = c2->modelMat();
		mAux = translate(mAux, dvec3(0, 0, 110));
		mAux = rotate(mAux, radians(-90.0), dvec3(0, 1, 0));
		c2->setModelMat(mAux);
		helices->addEntity(c2);

		CompoundEntity* chasis = new CompoundEntity();
		chasis->addEntity(helices);
		Sphere* bola = new Sphere(100.0);
		bola->setQuadricObjColor({ 1, 0, 0 });
		chasis->addEntity(bola);

		Plane* avion = new Plane();
		gObjects.push_back(avion);
		avion->addEntity(chasis);
		Cubo* alas = new Cubo(100);
		//color COBRE
		alas->changeColor(dvec4(0.462, 0.235, 0.156,1));
		Material* coppMat = new Material();
		coppMat->setCopper();
		alas->setMaterial(coppMat);
		mAux = alas->modelMat();
		mAux = scale(mAux, dvec3(4,0.3, 1.5));
		alas->setModelMat(mAux);
		avion->addEntity(alas);

		mAux = avion->modelMat();
		mAux = translate(mAux, dvec3(0, 260, 0));
		mAux = scale(mAux, dvec3(0.3, 0.3, 0.3));
		avion->setModelMat(mAux);
		sceneLights.push_back(avion->getLight());
		avion->setHelices(helices);
		scenePlane = avion;

		//Cono* c = new Cono(200,100,30);
		//c->changeColor(dvec4(0, 0, 1, 1));
		//gObjects.push_back(c);

		Esfera* es = new Esfera(200, 200, 200);
		//color AZUL
		es->changeColor(dvec4(0.403, 0.925, 0.956, 1));
		//color ORO
		//es->changeColor(dvec4(0.854, 0.647, 0.125, 1));
		Material* goldMat = new Material();
		goldMat->setGold();
		es->setMaterial(goldMat);
		gObjects.push_back(es);

	}
	else if (mId == 2) {

		Disk* disco = new Disk(150, 250);
		disco->setQuadricObjColor({ 0.776, 0, 0.003 });
		glm::dmat4 mAux = disco->modelMat();
		mAux = translate(mAux, dvec3(0, 200, 0));
		mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0, 0));
		disco->setModelMat(mAux);
		gObjects.push_back(disco);

		Sphere* esfera = new Sphere(250.0);
		esfera->setQuadricObjColor({ 1, 0.6, 0.125 });
		gObjects.push_back(esfera);

		Cylinder* cono1 = new Cylinder(25.0, 0, 40.0);
		cono1->setQuadricObjColor({ 0.011, 0.756, 0.768 });
		mAux = cono1->modelMat();
		mAux = translate(mAux, dvec3(90, 100, 210));
		mAux = rotate(mAux, radians(25.0), dvec3(0, 1.0, 0));
		cono1->setModelMat(mAux);
		gObjects.push_back(cono1);

		Cylinder* cono2 = new Cylinder(25.0, 0, 40.0);
		cono2->setQuadricObjColor({ 0, 0, 0.996 });
		mAux = cono2->modelMat();
		mAux = translate(mAux, dvec3(210, 100, 90));
		mAux = rotate(mAux, radians(65.0), dvec3(0, 1.0, 0));
		cono2->setModelMat(mAux);
		gObjects.push_back(cono2);

		PartialDisk* discoPar = new PartialDisk(150, 230, 90, 180);
		discoPar->setQuadricObjColor({ 0, 0.996, 0 });
		mAux = discoPar->modelMat();
		mAux = translate(mAux, dvec3(100, 0, 100));
		mAux = rotate(mAux, radians(45.0), dvec3(0, 1.0, 0));
		discoPar->setModelMat(mAux);
		gObjects.push_back(discoPar);

	}else if (mId == 3) {

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
	else if (mId == 4) {

		Estrella3D* estrella = new Estrella3D(300, 100, 5, 200);
		gObjects.push_back(estrella);

		Caja* caja = new Caja(100);
		caja->setModelMat(translate(caja->modelMat(), dvec3(400.0, 0.0, 0.0)));
		gObjects.push_back(caja);

	}
	else if (mId == 5)
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
	glEnable(GL_NORMALIZE);

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

void Scene::setActiveLight(int index, bool active)
{
	if (active) sceneLights[index]->enable();
	else sceneLights[index]->disable();
}

//void Scene::sceneDirLight(Camera const& cam) const {
//	glEnable(GL_LIGHTING);
//	if(activeLight0) glEnable(GL_LIGHT0);
//	else glDisable(GL_LIGHT0);
//	glm::fvec4 posDir = { 1, 1, 1, 0 };
//	glMatrixMode(GL_MODELVIEW);
//	glLoadMatrixd(value_ptr(cam.viewMat()));
//	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
//	glm::fvec4 ambient = { 0, 0, 0, 1 };
//	glm::fvec4 diffuse = { 1, 1, 1, 1 };
//	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
//	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
//	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
//}
//void Scene::scenePosLight(Camera const& cam) const
//{
//	glEnable(GL_LIGHTING);
//	if (activeLight1) glEnable(GL_LIGHT1);
//	else glDisable(GL_LIGHT1);
//	glm::fvec4 posDir = { 700, 700, 0, 1 };
//	glMatrixMode(GL_MODELVIEW);
//	glLoadMatrixd(value_ptr(cam.viewMat()));
//	glLightfv(GL_LIGHT1, GL_POSITION, value_ptr(posDir));
//	glm::fvec4 ambient = { 0, 0, 0, 1 }; //
//	glm::fvec4 diffuse = { 0, 1, 0, 1 }; //color
//	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 }; //reflexion
//	glLightfv(GL_LIGHT1, GL_AMBIENT, value_ptr(ambient));
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, value_ptr(diffuse));
//	glLightfv(GL_LIGHT1, GL_SPECULAR, value_ptr(specular));
//}
//void Scene::sceneSpotLight(Camera const& cam) const
//{
//	glEnable(GL_LIGHTING);
//	if (activeLight2) glEnable(GL_LIGHT2);
//	else glDisable(GL_LIGHT2);
//	glm::fvec4 posDir = { 0, 0, 300, 1 };
//	glMatrixMode(GL_MODELVIEW);
//	glLoadMatrixd(value_ptr(cam.viewMat()));
//	glLightfv(GL_LIGHT2, GL_POSITION, value_ptr(posDir));
//	glm::fvec4 ambient = { 0, 0, 0, 1 }; //
//	glm::fvec4 diffuse = { 0, 1, 0, 1 }; //color
//	glm::fvec4 specular = { 0, 0, 0, 1 }; //reflexion
//	glLightfv(GL_LIGHT2, GL_AMBIENT, value_ptr(ambient));
//	glLightfv(GL_LIGHT2, GL_DIFFUSE, value_ptr(diffuse));
//	glLightfv(GL_LIGHT2, GL_SPECULAR, value_ptr(specular));
//
//	float semiAplitud = 90.0;
//	float epsilon = 0.0;
//	glm::fvec3 dir = { .0,.0,-1.0 };
//	dir = normalize(dir);
//
//	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, semiAplitud);
//	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, epsilon);
//	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, value_ptr(dir));
//}
void Scene::setLightOff()
{
	//activeLight0 = false;
	//activeLight1 = false;
	//activeLight2 = false;

	for (Light* l : sceneLights) l->disable();

	GLfloat amb[] = { 0, 0, 0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}
void Scene::setLights()
{
	glEnable(GL_LIGHTING);

	directionalLight = new DirLight();
	directionalLight->setPosDir({1,1,1});

	positionalLight = new PosLight();
	positionalLight->setPosDir({300,300,0});
	positionalLight->setDiff({0,1,0,1});

	spotSceneLight = new SpotLight();
	spotSceneLight->setPosDir({ 0, 0, 300 });
	spotSceneLight->setSpot({ .0,.0,-1.0 }, 90.0, 0.0);
	spotSceneLight->setDiff({ 0,1,0,1 });

	mineroLight = new DirLight();
	mineroLight->setPosDir({ 0, 0, 1 });
	mineroLight->setAmb({0,0,0,1});
	mineroLight->setDiff({0.8,0.8,0.8,1});

	sceneLights.push_back(directionalLight);
	sceneLights.push_back(positionalLight);
	sceneLights.push_back(spotSceneLight);
	sceneLights.push_back(mineroLight);
}
void Scene::move()
{
	if (scenePlane != nullptr) {

		GLdouble radiusTranslation = 260, speedRotation = 4.0, speedTranslation = 4.0;

		dmat4 mI = dmat4(1);	//matriz unidad
		dmat4 rMat = rotate(mI, radians((speedRotation * frame)), dvec3(1.0, 0.0, 0.0));
		dmat4 tMat = translate(mI, dvec3(0.0,
			-cos(radians((speedTranslation * frame) - 180)) * radiusTranslation,
			-sin(radians((speedTranslation * frame) - 180)) * radiusTranslation));
		dmat4 sMat = scale(mI, dvec3(0.3, 0.3, 0.3));
		scenePlane->setModelMat(tMat * rMat * sMat * mI);
		frame++;
		//dmat4 mAux = scenePlane->modelMat();
		////mAux = translate(mAux,dvec3(0,0,0));
		//mAux = translate(mAux, dvec3(0.0, (sin(radians(currentAngle)) * 15), cos(radians(currentAngle)) * 15));
		//currentAngle++;
	}
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
	//sceneDirLight(cam);
	//scenePosLight(cam);
	//sceneSpotLight(cam);
	for (int i = 0; i < 3; i++) {
		sceneLights[i]->upload(cam.viewMat());
	}
	mineroLight->upload(dmat4(1.0));

	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
		el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------


