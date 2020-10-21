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
	Aspa** arrayAspas;
	int numAspas;
	int radio = 100;

	void giraMolino();

public:
	AspasMolino(int numA, Ogre::SceneNode* parent, Ogre::SceneManager* mSM);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

