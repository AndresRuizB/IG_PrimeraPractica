#pragma once
#include "AspasMolino.h"

class Molino : public EntidadIG
{
protected:
	Ogre::SceneNode* techoNode;
	Ogre::SceneNode* cuerpoNode;

	//Ogre::SceneNode* ficticioNode;
	AspasMolino* aspas = nullptr;

public:
	Molino(Ogre::SceneNode* node);
	~Molino() { delete aspas; }
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

