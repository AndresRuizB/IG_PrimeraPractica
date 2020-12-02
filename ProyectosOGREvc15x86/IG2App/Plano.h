#pragma once
#include "EntidadIG.h"

class Plano : public EntidadIG
{
private:
	Ogre::MovablePlane* mpRef;
	Ogre::Entity* entEP;
public:
	Plano(Ogre::SceneNode* node, int i = -1);
	~Plano() { if (mpRef) delete mpRef; mpRef = nullptr; };

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	void setReflejo(Ogre::Camera* camRef);
};

