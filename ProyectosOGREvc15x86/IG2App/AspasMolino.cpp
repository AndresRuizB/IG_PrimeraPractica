#include "AspasMolino.h"

void AspasMolino::giraMolino()
{
	aspasNode->roll(Ogre::Degree(2), Ogre::Node::TS_LOCAL);

	for (int i = 0; i < numAspas; i++) {
		arrayAspas[i]->roll(Ogre::Degree(2));
	}
}

AspasMolino::AspasMolino(int numA, Ogre::SceneNode* node, Ogre::SceneManager* mSceneManager) : numAspas(numA)
{
	arrayAspas = new Aspa * [numAspas];

	aspasNode = node;
	mSM = mSceneManager;
	aspasNode->translate(0,0,150, Ogre::Node::TS_WORLD);

	centroNode = aspasNode->createChildSceneNode("nCentro");
	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	centroNode->attachObject(cilindro);
	centroNode->pitch(Ogre::Degree(90));
	centroNode->setScale(18, 10, 18);

	for (int i = 0; i < numAspas; i++) {
		Ogre::Degree ang = Ogre::Degree(360.0 / numAspas * i);
		Ogre::SceneNode* aspaNode = aspasNode->createChildSceneNode("nAspa" + std::to_string(i));
		arrayAspas[i] = new Aspa(aspaNode, mSM, i, ang);
	}

}

void AspasMolino::orbitaMolino()
{
	//el truco
	aspasNode->translate(0, 0, -150, Ogre::Node::TS_LOCAL);
	aspasNode->yaw(Ogre::Degree(-3), Ogre::Node::TS_PARENT);
	aspasNode->translate(0, 0, 150, Ogre::Node::TS_LOCAL);

}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) {
		giraMolino();
	}
	else if (evt.keysym.sym == SDLK_c) {
		centroNode->translate(0, 0, -5);
	}

	return true;
}