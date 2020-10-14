#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

class Aspa : public OgreBites::InputListener { //#include <OgreInput.h>
protected:
	Ogre::SceneNode* aspaNode;
	Ogre::SceneNode* tableroNode;
	Ogre::SceneNode* cilindroNode;
public:
	Aspa(Ogre::SceneNode* aspaN, Ogre::SceneNode* tableroN, Ogre::SceneNode* cilindroN); // #include <OgreSceneNode.h>
	~Aspa() {};
	// M�todos de InputListener que pueden redefinirse
	//virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	//virtual bool keyReleased(const OgreBites::KeyboardEvent& evt);
	//virtual bool mousePressed(const OgreBites::MouseButtonEvent& evt);
	//virtual bool mouseRelease(const OgreBites::MouseButtonEvent& evt);
	//virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
	//virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt);

};
