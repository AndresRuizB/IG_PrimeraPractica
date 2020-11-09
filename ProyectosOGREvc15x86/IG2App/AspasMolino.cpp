#include "AspasMolino.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "EntidadIG.h"

void AspasMolino::giraMolino()
{
	mNode->roll(Ogre::Degree(-2), Ogre::Node::TS_LOCAL);

	for (int i = 0; i < numAspas; i++) {
		arrayAspas[i]->roll(Ogre::Degree(-2));
	}
}

AspasMolino::AspasMolino(int numA, Ogre::SceneNode* node) : numAspas(numA), EntidadIG(node)
{
	arrayAspas = new Aspa * [numAspas];

	mSM = mNode->getCreator();
	mNode->translate(0,0,150, Ogre::Node::TS_WORLD);

	centroNode = mNode->createChildSceneNode("nCentro");
	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/frenteMolino");
	centroNode->attachObject(cilindro);
	centroNode->pitch(Ogre::Degree(90));
	centroNode->setScale(18, 10, 18);

	for (int i = 0; i < numAspas; i++) {
		Ogre::Degree ang = Ogre::Degree(360.0 / numAspas * i);
		Ogre::SceneNode* aspaNode = mNode->createChildSceneNode("nAspa" + std::to_string(i));
		arrayAspas[i] = new Aspa(aspaNode, i, ang);
	}

}

AspasMolino::AspasMolino(int numA,int numAspasScene, Ogre::SceneNode* node) : numAspas(numA), EntidadIG(node)
{
	arrayAspas = new Aspa * [numAspas];

	mNode->translate(0, 0, 150, Ogre::Node::TS_WORLD);

	centroNode = mNode->createChildSceneNode("nCentro" + std::to_string(numAspasScene));
	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/frenteMolino");
	centroNode->attachObject(cilindro);
	centroNode->pitch(Ogre::Degree(90));
	centroNode->setScale(18, 10, 18);

	int offset = numAspas * numAspasScene;

	for (int i = 0; i < numAspas; i++) {
		Ogre::Degree ang = Ogre::Degree(360.0 / numAspas * i);
		Ogre::SceneNode* aspaNode = mNode->createChildSceneNode("nAspa" + std::to_string(offset+i));
		arrayAspas[i] = new Aspa(aspaNode, offset+i, ang);
	}

}

AspasMolino::~AspasMolino()
{
	for (int i = 0; i < numAspas; i++) {
		delete arrayAspas[i];
	}
	delete[] arrayAspas;
	arrayAspas = nullptr;
}

void AspasMolino::orbitaMolino()
{
	//el truco
	mNode->translate(0, 0, -150, Ogre::Node::TS_LOCAL);
	mNode->yaw(Ogre::Degree(-3), Ogre::Node::TS_PARENT);
	mNode->translate(0, 0, 150, Ogre::Node::TS_LOCAL);

}

void AspasMolino::ocultaAdornos()
{
	for (int i = 0; i < numAspas; i++) {
		arrayAspas[i]->ocultaAdorno();
	}
}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) {
		giraMolino();
	}
	else if (evt.keysym.sym == SDLK_c) {
		centroNode->translate(0, 0, -5);
	}

	return true;
}

void AspasMolino::frameRendered(const Ogre::FrameEvent& evt)
{
	/*Ogre::Real time = evt.timeSinceLastFrame;*/
	giraMolino();
}
