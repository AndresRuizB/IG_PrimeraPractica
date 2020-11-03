#include "Plano.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>

Plano::Plano(Ogre::SceneNode* parent) : EntidadIG(parent)
{

	Ogre::Entity* e = mSM->createEntity("mPlane1080x800");

	mNode->attachObject(e);
}
