#pragma once
#include "EntidadIG.h"
class Boya :
	public EntidadIG
{
private:

	Ogre::AnimationState* animationState;
public:
	Boya(Ogre::SceneNode* node);
	~Boya();

	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

