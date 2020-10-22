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
	Ogre::SceneNode* centroNode;
	Aspa** arrayAspas;
	int numAspas;

	void giraMolino();

public:
	AspasMolino(int numA, Ogre::SceneNode* node, Ogre::SceneManager* mSM);

	void orbitaMolino();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	
};

