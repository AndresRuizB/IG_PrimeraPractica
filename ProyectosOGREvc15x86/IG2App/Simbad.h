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
	bool alternateAnimation;
	bool alternateSword;
	bool walking;

	void createAnimWalk();
public:
	Simbad(Ogre::SceneNode* node);
	~Simbad() {};

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

