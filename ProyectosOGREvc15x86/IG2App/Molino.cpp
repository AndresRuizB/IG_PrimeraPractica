#include "Molino.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "EntidadIG.h"

Molino::Molino(Ogre::SceneNode* node) : EntidadIG(node)
{
	aspasMov = true;

	mNode->translate(330,120,-250);

	techoNode = mNode->createChildSceneNode("nTecho");
	Ogre::Entity* e = mSM->createEntity("sphere.mesh");
	e->setMaterialName("Practica1/cabezaMolino");
	techoNode->attachObject(e);
	techoNode->setScale(1.3, 1.3, 1.3);
	techoNode->translate(0, 50, 0);
	cuerpoNode = mNode->createChildSceneNode("nCuerpoMolino");
	e = mSM->createEntity("Barrel.mesh");
	e->setMaterialName("Practica1/cuerpoMolino");
	cuerpoNode->attachObject(e);
	cuerpoNode->setScale(55, 60, 55);
	cuerpoNode->translate(0, -150, 0);

	//ficticioNode = techoNode->createChildSceneNode();

	//Ogre::SceneNode* aspasNode = ficticioNode->createChildSceneNode("nAspas");
	Ogre::SceneNode* aspasNode = mNode->createChildSceneNode("nAspas");
	aspas = new AspasMolino(6,2,aspasNode);
}

void Molino::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	switch (msgType)
	{
	case EventoR:
	{
		techoNode->detachAllObjects();
		Ogre::Entity* e = mSM->createEntity("sphere.mesh");
		e->setMaterialName("IG2/NormalesGS");
		techoNode->attachObject(e);
		aspasMov = false;
		aspas->ocultaAdornos();
	}
		break;
	default:
		break;
	}
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_h) {
		aspas->orbitaMolino();
		//ficticioNode->yaw(Ogre::Degree(10));
	}
	else if (evt.keysym.sym == SDLK_r) {
		sendEvent(EventoR,this);
	}
	aspas->keyPressed(evt);

	return true;
}

void Molino::frameRendered(const Ogre::FrameEvent& evt)
{
	if(aspasMov)
	aspas->frameRendered(evt);
}
