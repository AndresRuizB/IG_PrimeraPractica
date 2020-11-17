#pragma once
#include "EntidadIG.h"
class Simbad :
	public EntidadIG
{
private:
	Ogre::Entity* ent = nullptr;
	Ogre::AnimationState* animDance;
	Ogre::AnimationState* animTop;
	Ogre::AnimationState* animBot;
	Ogre::AnimationState* animWalk;
	Ogre::Entity* espada = nullptr;

	bool sinbadEstaBailando = false;
	bool espadaEnManoDer = false;

	void creaAnimacionCaminar();

public:
	Simbad(Ogre::SceneNode* node);
	~Simbad();

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
};

