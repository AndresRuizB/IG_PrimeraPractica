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

	aspasNode = parent->createChildSceneNode("nAspas");

	for (int i = 0; i < numA; i++) {
		Ogre::Degree ang = Ogre::Degree(360.0 / numA * i);
		arrayAspas[i] = new Aspa(aspasNode, mSM, i, ang);
	}

	cilindroCentral = parent->createChildSceneNode("nCilindroCentral");

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
	}

	return false;
}