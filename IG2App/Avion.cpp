#include "Avion.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>

Avion::Avion(Ogre::SceneNode* parent) : EntidadIG(parent)
{
	mNode = parent->createChildSceneNode("nAvionNodo");
	Ogre::Entity* aux;

	cuerpoNode = mNode->createChildSceneNode("nCuerpoAvion");
	aux = mSM->createEntity("sphere.mesh");
	cuerpoNode->attachObject(aux);

	aux = mSM->createEntity("cube.mesh");
	alaDNode = mNode->createChildSceneNode("nAlaDerecha");
	alaDNode->attachObject(aux);
	alaDNode->setScale(3.5, 0.1, 1.5);
	alaDNode->translate(-100, 0, 0);

	aux = mSM->createEntity("cube.mesh");
	alaINode = mNode->createChildSceneNode("nAlaIzquierda");
	alaINode->attachObject(aux);
	alaINode->setScale(3.5, 0.1, 1.5);
	alaINode->translate(100, 0, 0);

	aux = mSM->createEntity("Barrel.mesh");
	frenteNode = mNode->createChildSceneNode("nfrenteAvion");
	frenteNode->attachObject(aux);
	frenteNode->setScale(10, 10, 10);
	frenteNode->pitch(Ogre::Degree(90));
	frenteNode->translate(0, 0, 90);

	aux = mSM->createEntity("ninja.mesh");
	pilotoNode = mNode->createChildSceneNode("nPilotoAvion");
	pilotoNode->attachObject(aux);
	frenteNode->setScale(0.3, 0.3, 0.3);
	pilotoNode->yaw(Ogre::Degree(180));
	pilotoNode->translate(0, -10, 0);

	heliceDerAux = mNode->createChildSceneNode("nHeliceDerAvion");
	heliceDerNode = new AspasMolino(3, heliceDerAux, 1);
	heliceDerAux->setScale(0.5,0.5,0.5);
	heliceDerAux->translate(-240,0,80);

	heliceIzAux = mNode->createChildSceneNode("nHeliceIzAvion");
	heliceIzNode = new AspasMolino(3, heliceIzAux, 2);
	heliceIzAux->setScale(0.5, 0.5, 0.5);
	heliceIzAux->translate(240, 0, 80);
}

Avion::~Avion()
{
	delete heliceDerNode;
	delete heliceIzNode;
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	heliceDerNode->giraMolino();
	heliceIzNode->giraMolino();
	return false;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	/*heliceIzNode->frameRendered(evt);
	heliceDerNode->frameRendered(evt);*/
}
