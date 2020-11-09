#include "Simbad.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>

Simbad::Simbad(Ogre::SceneNode* node) : EntidadIG(node)
{
	Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(ent);
}
