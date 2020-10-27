#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "Aspa.h"

class AspasMolino
{
private:
	Ogre::SceneNode* aspasNode;
	Ogre::SceneNode* cilindroCentral;
	Aspa** arrayAspas;
	int numAspas;


public:
	AspasMolino(int numA, Ogre::SceneNode* parent, Ogre::SceneManager* mSM);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void giraMolino();
};

