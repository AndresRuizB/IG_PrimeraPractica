#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* parentNode, Ogre::SceneManager* mSM, int index, Ogre::Degree ang) :mSM_(mSM)
{
	aspaNode = parentNode->createChildSceneNode("nAspa" + std::to_string(index));

	tableroNode = aspaNode->createChildSceneNode("nTablero" + std::to_string(index));
	Ogre::Entity* cubo = mSM->createEntity("cube.mesh");
	tableroNode->attachObject(cubo);
	tableroNode->setScale(3, 0.6, 0.25);
	tableroNode->setPosition(130, 0, 0);

	cilindroNode = aspaNode->createChildSceneNode("nAdorno" + std::to_string(index));
	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cilindroNode->attachObject(cilindro);
	cilindroNode->setScale(7, 12, 7);
	cilindroNode->translate(250, 0, 20);

	cilindroNode->roll(-ang);

	aspaNode->roll(ang);
}

void Aspa::roll(Ogre::Degree a){

	cilindroNode->roll(Ogre::Degree(-a));
}
