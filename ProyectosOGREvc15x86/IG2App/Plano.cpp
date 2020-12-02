#include "Plano.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreMovablePlane.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>

using namespace Ogre;

Plano::Plano(Ogre::SceneNode* node, int i) : EntidadIG(node) , mpRef(nullptr)
{
	entEP = mSM->createEntity("mPlane1080x800");
	if (i == -1) {
		entEP->setMaterialName("IG2App/reflejo");
	}
	else entEP->setMaterialName("Practica1/plano" + std::to_string(i));
	mNode->attachObject(entEP);
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

void Plano::setReflejo(Ogre::Camera* camRef)
{
	mpRef = new MovablePlane(Vector3::UNIT_Y, 0);
	mNode->attachObject(mpRef);

	camRef->enableReflection(mpRef);
	camRef->enableCustomNearClipPlane(mpRef);

	TextureUnitState* tu = entEP->getSubEntity(0)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState("rttReflejo"); // <- (*)
	tu->setColourOperation(LBO_ADD);
	tu->setProjectiveTexturing(true, camRef);
}
