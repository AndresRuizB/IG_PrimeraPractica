#pragma once
#include "AspasMolino.h"

class Avion : public EntidadIG
{
private:

	Ogre::SceneNode* cuerpoNode;
	Ogre::SceneNode* alaINode;
	Ogre::SceneNode* alaDNode;
	Ogre::SceneNode* frenteNode;
	Ogre::SceneNode* pilotoNode;
	Ogre::SceneNode* mLightNode;
	AspasMolino* heliceINode;
	AspasMolino* heliceDNode;
	Ogre::Light* luzAvion = nullptr;

	bool rWasPressed = false;

public:
	Avion(Ogre::SceneNode* node);
	~Avion() { delete heliceINode; delete heliceDNode; };

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
};

