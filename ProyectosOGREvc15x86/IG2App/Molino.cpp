#include "Molino.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "EntidadIG.h"

Molino::Molino(Ogre::SceneNode* node) : EntidadIG(node)
{
	mNode->translate(330, 120, -250);

	techoNode = mNode->createChildSceneNode("nTecho");
	techo = mSM->createEntity("sphere.mesh");
	techo->setMaterialName("techoMolino");
	techoNode->attachObject(techo);
	techoNode->setScale(1.3, 1.3, 1.3);
	techoNode->translate(0, 50, 0);
	Ogre::Entity* c = mSM->createEntity("Barrel.mesh");
	cuerpoNode = mNode->createChildSceneNode("nCuerpoMolino");
	c->setMaterialName("cuerpoMolino");
	cuerpoNode->attachObject(c);
	cuerpoNode->setScale(55, 60, 55);
	cuerpoNode->translate(0, -150, 0);

	//ficticioNode = techoNode->createChildSceneNode();

	//Ogre::SceneNode* aspasNode = ficticioNode->createChildSceneNode("nAspas");
	Ogre::SceneNode* aspasNode = mNode->createChildSceneNode("nAspas");
	aspas = new AspasMolino(6, 2, aspasNode);
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_h) {
		aspas->orbitaMolino();
		//ficticioNode->yaw(Ogre::Degree(10));
	}
	aspas->keyPressed(evt);

	return true;
}

void Molino::frameRendered(const Ogre::FrameEvent& evt)
{
	if (!rWasPressed)
	{
		aspas->frameRendered(evt);
	}
}

void Molino::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	switch (msgType)
	{
	case R_KEY:
		rWasPressed = true;
		aspas->ocultaAdornos();
		techo->setMaterialName("techoMolinoAlt");
		break;
	default:
		break;
	}

}