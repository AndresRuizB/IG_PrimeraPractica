#pragma once
#include "EntidadIG.h"

class Plano : public EntidadIG
{
private:
public:

	Ogre::MovablePlane* mpRef;
	Ogre::Entity* entEp;

	Plano(Ogre::SceneNode* node, int i = -1);
	~Plano();

	void setCameraReflejo(Ogre::Camera* camRef);
	void deatach();

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
};

