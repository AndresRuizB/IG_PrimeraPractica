#pragma once
#include "EntidadIG.h"
class Simbad : public EntidadIG
{
private:
	Ogre::Entity* simbadEntity;
	Ogre::Entity* swordEntity;
	Ogre::AnimationState* animationStateDance;
	Ogre::AnimationState* animationStateRunT;
	Ogre::AnimationState* animationStateRunB;
	Ogre::AnimationState* animationStateWalk;
	Ogre::AnimationState* animationStateIdleT;
	bool alternateAnimation;
	bool alternateSword;
	bool walking;
	bool dead;

	void createAnimWalk();
	void die();
public:
	Simbad(Ogre::SceneNode* node);
	~Simbad() {};

	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

