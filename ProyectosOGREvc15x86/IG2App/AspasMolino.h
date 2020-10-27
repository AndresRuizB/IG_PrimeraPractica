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
	Ogre::SceneManager* mSM;
	Aspa** arrayAspas;
	int numAspas;

	void giraMolino();

public:
	AspasMolino(int numA, Ogre::SceneNode* node);
	/*Constructora para el avion*/
	AspasMolino(int numA,int numHelice, Ogre::SceneNode* node);
	~AspasMolino();
	void orbitaMolino();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	
};

