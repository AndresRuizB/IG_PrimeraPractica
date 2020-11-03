#include "Avion.h"
#include "EntidadIG.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>

Avion::Avion(Ogre::SceneNode* node) : EntidadIG(node)
{

	cuerpoNode = mNode->createChildSceneNode("nCuerpoAvion");
	Ogre::Entity* e = mSM->createEntity("sphere.mesh");
	cuerpoNode->attachObject(e);
	cuerpoNode->setScale(1.4, 1.4, 1.4);

	alaDNode = mNode->createChildSceneNode("nAlaD");
	e = mSM->createEntity("cube.mesh");
	alaDNode->attachObject(e);
	alaDNode->setScale(2.8, 0.2, 1);
	alaDNode->translate(270, 0, 0);

	alaINode = mNode->createChildSceneNode("nAlaI");
	e = mSM->createEntity("cube.mesh");
	alaINode->attachObject(e);
	alaINode->setScale(2.8, 0.2, 1);
	alaINode->translate(-270, 0, 0);

	frenteNode = mNode->createChildSceneNode("nFrente");
	e = mSM->createEntity("Barrel.mesh");
	frenteNode->attachObject(e);
	frenteNode->pitch(Ogre::Degree(90));
	frenteNode->setScale(15, 5, 15);
	frenteNode->translate(0, 0, 150);

	pilotoNode = mNode->createChildSceneNode("nPiloto");
	e = mSM->createEntity("ninja.mesh");
	pilotoNode->attachObject(e);
	pilotoNode->yaw(Ogre::Degree(180));

	Ogre::SceneNode* hN = mNode->createChildSceneNode("nHeliceD");
	hN->translate(270,0,-94);
	hN->setScale(0.25, 0.25, 0.25);
	heliceDNode = new AspasMolino(5,0,hN);

	hN = mNode->createChildSceneNode("nHeliceI");
	hN->translate(-270, 0, -94);
	hN->setScale(0.25, 0.25, 0.25);
	heliceINode = new AspasMolino(5,1,hN);

}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) {
		heliceDNode->keyPressed(evt);
		heliceINode->keyPressed(evt);
	}

	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	heliceDNode->frameRendered(evt);
	heliceINode->frameRendered(evt);
}
