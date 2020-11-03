#include "Plano.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "EntidadIG.h"

using namespace Ogre;

Plano::Plano(Ogre::SceneNode* node) : EntidadIG(node)
{
	Ogre::Entity* e = mSM->createEntity("mPlane1080x800");

	mNode->attachObject(e);
}
