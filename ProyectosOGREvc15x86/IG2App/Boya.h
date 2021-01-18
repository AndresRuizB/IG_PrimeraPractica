#pragma once
#include "EntidadIG.h"
class Boya : public EntidadIG
{
protected:
	Ogre::AnimationState* animationState;
	Ogre::Entity* entity = nullptr;
public:
	Boya(Ogre::SceneNode* node);
	~Boya() {};

	//virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
};

