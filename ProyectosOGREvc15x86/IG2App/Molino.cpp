#include "Molino.h"

Molino::Molino(Ogre::SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();

	mNode->translate(0,0,-150);

	techoNode = mNode->createChildSceneNode("nTecho");
	Ogre::Entity* e = mSM->createEntity("sphere.mesh");
	techoNode->attachObject(e);
	techoNode->setScale(1.3, 1.3, 1.3);
	techoNode->translate(0, 50, 0);
	cuerpoNode = mNode->createChildSceneNode("nCuerpo");
	e = mSM->createEntity("Barrel.mesh");
	cuerpoNode->attachObject(e);
	cuerpoNode->setScale(55, 60, 55);
	cuerpoNode->translate(0, -150, 0);

	//ficticioNode = techoNode->createChildSceneNode();

	//Ogre::SceneNode* aspasNode = ficticioNode->createChildSceneNode("nAspas");
	Ogre::SceneNode* aspasNode = mNode->createChildSceneNode("nAspas");
	aspas = new AspasMolino(6,aspasNode,mSM);

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
