#pragma once
#include "EntidadIG.h"

class Plano : public EntidadIG
{
private:
	Ogre::Entity* e;
	std::string textName;
public:
	Plano(Ogre::SceneNode* node);
	Plano(Ogre::SceneNode* node, std::string matName);

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
};

