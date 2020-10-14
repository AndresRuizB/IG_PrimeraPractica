#include "Aspa.h"
#include <SDL_keycode.h>

Aspa::Aspa(Ogre::SceneNode* aspaN, Ogre::SceneNode* tableroN, Ogre::SceneNode* cilindroN)
{
	aspaNode = aspaN;
	tableroNode = tableroN;
	cilindroNode = cilindroN;
	Ogre::SceneManager* mSM = aspaNode->getCreator();

	Ogre::Entity* e = mSM->createEntity("cube.mesh");
	tableroNode->attachObject(e);
	tableroNode->setScale(4, 0.5, 0.07);

	e = mSM->createEntity("Barrel.mesh");
	cilindroNode->attachObject(e);
	cilindroNode->setPosition(200, 0, 0);
	cilindroNode->setScale(3.5, 5.5, 3.5);
}

bool Aspa::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) // #include <SDL_keycode.h>
	{
		cilindroNode->roll(Ogre::Degree(-5));
	}
	return true;
}
