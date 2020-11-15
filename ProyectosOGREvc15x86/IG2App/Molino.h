#pragma once
#include "AspasMolino.h"

class Molino : public EntidadIG
{
protected:
	Ogre::SceneNode* techoNode;
	Ogre::SceneNode* cuerpoNode;

	//Ogre::SceneNode* ficticioNode;
	AspasMolino* aspas = nullptr;
	Ogre::Entity* techo = nullptr;

	bool rWasPressed = false;

public:
	Molino(Ogre::SceneNode* node);
	~Molino() { delete aspas; }
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
};

