#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Aspa.h"

class AspasMolino : public OgreBites::InputListener { //#include <OgreInput.h>
protected:
	Ogre::SceneNode* aspasNode;
	int numAspas;
	Aspa** arrayAspas;

public:
	AspasMolino(Ogre::SceneNode* node, int nAspas); // #include <OgreSceneNode.h>
	~AspasMolino();
	// Métodos de InputListener que pueden redefinirse
	//virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	//virtual bool keyReleased(const OgreBites::KeyboardEvent& evt);
	//virtual bool mousePressed(const OgreBites::MouseButtonEvent& evt);
	//virtual bool mouseRelease(const OgreBites::MouseButtonEvent& evt);
	//virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
	//virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt);

};

