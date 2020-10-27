#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "AspasMolino.h"

class Molino
{
private:
	Ogre::SceneNode* mNode = nullptr;

	Ogre::SceneNode* techoNode = nullptr;
	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* aspasNode = nullptr;
	AspasMolino* aspas = nullptr;
public:
	Molino(Ogre::SceneManager* mSM);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

