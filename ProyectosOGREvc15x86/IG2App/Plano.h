#pragma once
#include "EntidadIG.h"

class Plano : public EntidadIG
{
private:
public:
	Plano(Ogre::SceneNode* node, int i = -1);
	~Plano() {};

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
};

