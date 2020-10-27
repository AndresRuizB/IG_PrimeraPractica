#include "Molino.h"

Molino::Molino(Ogre::SceneManager* mSM) {
	mNode = mSM->getRootSceneNode()->createChildSceneNode("nMolino");

	aspasNode = mNode->createChildSceneNode("nAspasMolino");
	aspas = new AspasMolino(9, aspasNode, mSM);
	aspasNode->setPosition(0, 190, 140);

	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");

	techoNode = mNode->createChildSceneNode("nTechoMolino");
	techoNode->attachObject(sphere);
	techoNode->setPosition(0, 190, 0);
	techoNode->setScale(1.2, 1.2, 1.2);

	cuerpoNode = mNode->createChildSceneNode("nCuerpoMolino");
	cuerpoNode->attachObject(cilindro);
	cuerpoNode->setScale(50, 60, 50);
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	aspas->keyPressed(evt);
	return false;
}
