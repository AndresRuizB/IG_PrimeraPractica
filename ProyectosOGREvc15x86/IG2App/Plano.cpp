#include "Plano.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "EntidadIG.h"

using namespace Ogre;

Plano::Plano(Ogre::SceneNode* node, int i) : EntidadIG(node)
{
	Ogre::Entity* e = mSM->createEntity("mPlane1080x800");

	if(i!=-1)
		e->setMaterialName("Practica1/plano" + std::to_string(i));
	mNode->attachObject(e);
}

void Plano::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	switch (msgType)
	{
	case EventoR: 
	{
		mNode->detachAllObjects();
		Ogre::Entity* e = mSM->createEntity("mPlane1080x800");
		e->setMaterialName("Practica1/fondoRio");
		mNode->attachObject(e);
	}
		break;
	default:
		break;
	}
}
