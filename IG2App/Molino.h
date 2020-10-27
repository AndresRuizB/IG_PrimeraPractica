#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "AspasMolino.h"

class Molino : public OgreBites::InputListener
{
private:
	Ogre::SceneNode* mNode = nullptr;

	Ogre::SceneNode* techoNode = nullptr;
	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* aspasNode = nullptr;
	Ogre::SceneNode* auxNode = nullptr;

	AspasMolino* aspas = nullptr;

	void orbitaAspas();
public:
	Molino(Ogre::SceneManager* mSM);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

