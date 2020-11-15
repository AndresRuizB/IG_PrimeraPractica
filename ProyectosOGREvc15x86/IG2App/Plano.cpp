#include "Plano.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "EntidadIG.h"
#include <iostream>

using namespace Ogre;

Plano::Plano(Ogre::SceneNode* node) : EntidadIG(node)
{
	e = mSM->createEntity("mPlane1080x800");

	mNode->attachObject(e);
}

Plano::Plano(Ogre::SceneNode* node, std::string matName) : EntidadIG(node), textName(matName)
{
	e = mSM->createEntity("mPlane1080x800");
	e->setMaterialName(matName);

	mNode->attachObject(e);
}

void Plano::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	switch (msgType)
	{
	case R_KEY:
		
		if(textName == "planoAgua")
		e->setMaterialName("piedrasRio");
		break;
	default:
		break;
	}

}
