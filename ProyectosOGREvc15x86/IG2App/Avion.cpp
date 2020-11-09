#include "Avion.h"
#include "EntidadIG.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>

Avion::Avion(Ogre::SceneNode* node) : EntidadIG(node)
{
	avionMov = true;
	//FOCO
	Ogre::SceneNode* lightNode = mSM->createSceneNode();
	mNode->addChild(lightNode);
	luzFoco = mSM->createLight("Luz Foco");
	luzFoco->setType(Ogre::Light::LT_SPOTLIGHT);
	luzFoco->
		setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	luzFoco->setDirection(Ogre::Vector3(1, -1, 0));
	luzFoco->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	luzFoco->setSpotlightOuterAngle(Ogre::Degree(45.0f));
	luzFoco->setSpotlightFalloff(0.0f);
	lightNode->attachObject(luzFoco);
	//-----------------------------------------------------------------------

	cuerpoNode = mNode->createChildSceneNode("nCuerpoAvion");
	Ogre::Entity* e = mSM->createEntity("sphere.mesh");
	e->setMaterialName("Practica1/cuerpoAvion");
	cuerpoNode->attachObject(e);
	cuerpoNode->setScale(1.4, 1.4, 1.4);

	alaDNode = mNode->createChildSceneNode("nAlaD");
	e = mSM->createEntity("cube.mesh");
	e->setMaterialName("Practica1/ala");
	alaDNode->attachObject(e);
	alaDNode->setScale(2.8, 0.2, 1);
	alaDNode->translate(270, 0, 0);

	alaINode = mNode->createChildSceneNode("nAlaI");
	e = mSM->createEntity("cube.mesh");
	e->setMaterialName("Practica1/ala");
	alaINode->attachObject(e);
	alaINode->setScale(2.8, 0.2, 1);
	alaINode->translate(-270, 0, 0);

	frenteNode = mNode->createChildSceneNode("nFrente");
	e = mSM->createEntity("Barrel.mesh");
	e->setMaterialName("Practica1/frenteAvion");
	frenteNode->attachObject(e);
	frenteNode->pitch(Ogre::Degree(90));
	frenteNode->setScale(15, 5, 15);
	frenteNode->translate(0, 0, 150);

	pilotoNode = mNode->createChildSceneNode("nPiloto");
	e = mSM->createEntity("ninja.mesh");
	e->setMaterialName("Practica1/ninja");
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

void Avion::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	switch (msgType)
	{
	case EventoR: 
	{
		luzFoco->setVisible(false);
		avionMov = false;
	}
		break;
	default:
		break;
	}
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
	if (avionMov) {
		mNode->translate(300, 0, 0, Ogre::Node::TS_LOCAL);
		mNode->yaw(Ogre::Degree(1));
		mNode->translate(-300, 0, 0, Ogre::Node::TS_LOCAL);
	}

	heliceDNode->frameRendered(evt);
	heliceINode->frameRendered(evt);
}
