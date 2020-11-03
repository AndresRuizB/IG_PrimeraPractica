#pragma once

#include "EntidadIG.h"

class Aspa : public EntidadIG
{
private:
	Ogre::SceneNode *tableroNode, *cilindroNode;

public:
	Aspa(Ogre::SceneNode* parentNode, int index, Ogre::Degree ang);
	void roll(Ogre::Degree a);
};

