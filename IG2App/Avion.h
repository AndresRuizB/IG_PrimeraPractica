#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneNode.h>
#include "AspasMolino.h"
class Avion :public OgreBites::InputListener
{
private:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneManager* mSM_ = nullptr;

	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* alaINode = nullptr;
	Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* frenteNode = nullptr;
	Ogre::SceneNode* pilotoNode = nullptr;

	Ogre::SceneNode* heliceDerAux = nullptr;
	Ogre::SceneNode* heliceIzAux = nullptr;
	AspasMolino* heliceIzNode = nullptr;
	AspasMolino* heliceDerNode = nullptr;
public:

	Avion(Ogre::SceneNode* parent, Ogre::SceneManager* msm);
	~Avion();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

