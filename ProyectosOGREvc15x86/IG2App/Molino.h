#pragma once
#include "AspasMolino.h"

class Molino : public EntidadIG
{
protected:
	Ogre::SceneNode* techoNode;
	Ogre::SceneNode* cuerpoNode;
	bool aspasMov;

	//Ogre::SceneNode* ficticioNode;
	AspasMolino* aspas = nullptr;

public:
	Molino(Ogre::SceneNode* node);
	~Molino() { delete aspas; }

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

