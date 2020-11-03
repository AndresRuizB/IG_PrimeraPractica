#include "Molino.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

void Molino::orbitaAspas()
{
	/*aspasNode->translate(0, -190, -140, Ogre::Node::TS_LOCAL);
	aspasNode->yaw(Ogre::Degree(1));
	aspasNode->translate(0, 190, 140, Ogre::Node::TS_LOCAL);*/

	auxNode->yaw(Ogre::Degree(1));
}

Molino::Molino(Ogre::SceneNode* parent):EntidadIG(parent) {
	mNode = parent->createChildSceneNode("nMolino");	

	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");

	techoNode = mNode->createChildSceneNode("nTechoMolino");
	techoNode->attachObject(sphere);
	techoNode->translate(0, 190, 0);
	techoNode->setScale(1.2, 1.2, 1.2);

	cuerpoNode = mNode->createChildSceneNode("nCuerpoMolino");
	cuerpoNode->attachObject(cilindro);
	cuerpoNode->setScale(50, 60, 50);

	auxNode = techoNode->createChildSceneNode("nNodoAuxiliarMolino");
	aspasNode = auxNode->createChildSceneNode("nAspasMolino");
	aspasNode->setPosition(0, 0, 140);

	//aspasNode = mNode->createChildSceneNode("nAspasMolino");
	aspas = new AspasMolino(9, aspasNode);
	//aspasNode->setPosition(0, 190, 140);
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{

	if (evt.keysym.sym == SDLK_h) {
		orbitaAspas();
		return true;
	}

	aspas->keyPressed(evt);
	return false;
}
