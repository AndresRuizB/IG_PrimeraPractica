#pragma once
#include "EntidadIG.h"

class Aspa : public EntidadIG
{
private:
	Ogre::SceneNode* tableroNode, *cilindroNode;

public:
	Aspa(Ogre::SceneNode* node, int index, Ogre::Degree ang);
	~Aspa() {};
	void roll(Ogre::Degree a);
};

