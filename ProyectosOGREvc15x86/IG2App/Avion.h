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
	AspasMolino* heliceINode;
	AspasMolino* heliceDNode;

	bool avionMov;
	Ogre::Light* luzFoco;


public:
	Avion(Ogre::SceneNode* node);
	~Avion() { delete heliceINode; delete heliceDNode; };

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};
