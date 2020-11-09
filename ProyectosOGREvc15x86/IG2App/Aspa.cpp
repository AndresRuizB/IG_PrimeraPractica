#include "Aspa.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>

Aspa::Aspa(Ogre::SceneNode* node, int index, Ogre::Degree ang) : EntidadIG(node)
{

	tableroNode = mNode->createChildSceneNode("nTablero" + std::to_string(index));
	Ogre::Entity* cubo = mSM->createEntity("cube.mesh");
	cubo->setMaterialName("Practica1/aspa");
	tableroNode->attachObject(cubo);
	tableroNode->setScale(3, 0.6, 0.25);
	tableroNode->setPosition(130, 0, 0);

	cilindroNode = mNode->createChildSceneNode("nAdorno" + std::to_string(index));
	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/adorno");
	cilindroNode->attachObject(cilindro);
	cilindroNode->setScale(5, 9, 5);
	cilindroNode->translate(250, 0, 20);

	cilindroNode->roll(-ang);

	mNode->roll(ang);
}

void Aspa::roll(Ogre::Degree a){

	cilindroNode->roll(Ogre::Degree(-a));
}

void Aspa::ocultaAdorno()
{
	cilindroNode->setVisible(false);
}
