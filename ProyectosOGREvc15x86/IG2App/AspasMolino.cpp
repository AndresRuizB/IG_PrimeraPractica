#include "AspasMolino.h"

void AspasMolino::giraMolino()
{
	aspasNode->roll(Ogre::Degree(2));

	for (int i = 0; i < numAspas; i++) {

		arrayAspas[i]->roll(Ogre::Degree(2));
	}
}

AspasMolino::AspasMolino(int numA, Ogre::SceneNode* parent, Ogre::SceneManager* mSM) :numAspas(numA)
{
	arrayAspas = new Aspa * [numA];

	aspasNode = mSM->getRootSceneNode()->createChildSceneNode("nAspas");

	for (int i = 0; i < numA; i++) {
		Ogre::Degree ang = Ogre::Degree(360 / numA * i);
		arrayAspas[i] = new Aspa(aspasNode, mSM, i, ang);
	}

}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) {
		giraMolino();
		return true;
	}

	return false;
}