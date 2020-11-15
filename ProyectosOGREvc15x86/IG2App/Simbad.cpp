#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* node): EntidadIG(node)
{
	Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	mNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	mNode->attachObject(ent);
	mNode->setScale(15, 15, 15);
	mNode->translate(-350, -120, 230);
}

Simbad::~Simbad()
{
}
