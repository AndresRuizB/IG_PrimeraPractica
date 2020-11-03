#include "AspasMolino.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>

void AspasMolino::giraMolino()
{
	mNode->roll(Ogre::Degree(2));

	for (int i = 0; i < numAspas; i++) {

		arrayAspas[i]->roll(Ogre::Degree(2));
	}
}

void AspasMolino::mueveCentro()
{
	cilindroCentral->translate(0,0,-1);
}

AspasMolino::AspasMolino(int numA, Ogre::SceneNode* parent) :numAspas(numA), EntidadIG(parent)
{
	arrayAspas = new Aspa * [numA];

	mNode = parent->createChildSceneNode("nAspas");

	for (int i = 0; i < numA; i++) {
		Ogre::Degree ang = Ogre::Degree(360.0 / numA * i);
		arrayAspas[i] = new Aspa(mNode, i, ang);
	}

	cilindroCentral = parent->createChildSceneNode("nCilindroCentral");

	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cilindroCentral->attachObject(cilindro);
	cilindroCentral->setScale(10, 10, 10);
	cilindroCentral->pitch(Ogre::Radian(Ogre::Math::HALF_PI));

}

AspasMolino::AspasMolino(int numA, Ogre::SceneNode* parent, int index): numAspas(numA), EntidadIG(parent)
{
	arrayAspas = new Aspa * [numA];

	mNode = parent->createChildSceneNode(/*"nAspas" + index*/);

	for (int i = 0; i < numA; i++) {
		Ogre::Degree ang = Ogre::Degree(360.0 / numA * i);
		arrayAspas[i] = new Aspa(mNode, i+index*numA, ang);
	}

	cilindroCentral = parent->createChildSceneNode("nCilindroCentral"+index);

	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cilindroCentral->attachObject(cilindro);
	cilindroCentral->setScale(10, 10, 10);
	cilindroCentral->pitch(Ogre::Radian(Ogre::Math::HALF_PI));

}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) {
		giraMolino();
		return true;
	}else if (evt.keysym.sym == SDLK_c) {
		mueveCentro();
		return true;
	}

	return false;
}

void AspasMolino::frameRendered(const Ogre::FrameEvent& evt)
{
	/*Ogre::Real time = evt.timeSinceLastFrame;*/
	giraMolino();
}