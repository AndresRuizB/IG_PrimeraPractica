#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "AspasMolino.h"

class Molino : public OgreBites::InputListener
{
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	Ogre::SceneNode* techoNode;
	Ogre::SceneNode* cuerpoNode;

	//Ogre::SceneNode* ficticioNode;
	AspasMolino* aspas = nullptr;

public:
	Molino(Ogre::SceneNode* node);
	~Molino() { delete aspas; }
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

