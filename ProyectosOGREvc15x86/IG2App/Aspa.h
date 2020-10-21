#pragma once

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

class Aspa
{
private:
	Ogre::SceneNode* aspaNode, *tableroNode, *cilindroNode;
	Ogre::SceneManager* mSM_;

public:
	Aspa(Ogre::SceneNode* parentNode, Ogre::SceneManager* mSM, int index, Ogre::Degree ang);
	void roll(Ogre::Degree a);
};

