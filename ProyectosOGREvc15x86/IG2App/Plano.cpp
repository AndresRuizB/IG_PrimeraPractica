#include "Plano.h"
#include <OgreMeshManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "EntidadIG.h"

using namespace Ogre;

Plano::Plano(Ogre::SceneNode* node) : EntidadIG(node)
{
	mNode->translate(0, -200, 0);

	MeshManager::getSingleton().createPlane("mPlane1080x800",
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	Plane(Vector3::UNIT_Y, 0),
	1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	Ogre::Entity* e = mSM->createEntity("mPlane1080x800");

	mNode->attachObject(e);
}
