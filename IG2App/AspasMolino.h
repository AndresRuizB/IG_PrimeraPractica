#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "Aspa.h"

class AspasMolino : public OgreBites::InputListener
{
private:
	Ogre::SceneNode* aspasNode;
	Ogre::SceneNode* cilindroCentral;
	Aspa** arrayAspas;
	int numAspas;


	void mueveCentro();

public:
	AspasMolino(int numA, Ogre::SceneNode* parent, Ogre::SceneManager* mSM);
	AspasMolino(int numA, Ogre::SceneNode* parent, Ogre::SceneManager* mSM, int index);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);


	void giraMolino();
};

