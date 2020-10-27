#pragma once
#include "IG2ApplicationContext.h"
#include <OgreSceneNode.h>
#include "AspasMolino.h"

class Avion : public OgreBites::InputListener
{
private:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	Ogre::SceneNode* cuerpoNode;
	Ogre::SceneNode* alaINode;
	Ogre::SceneNode* alaDNode;
	Ogre::SceneNode* frenteNode;
	Ogre::SceneNode* pilotoNode;
	AspasMolino* heliceINode;
	AspasMolino* heliceDNode;


public:
	Avion(Ogre::SceneNode* node);
	~Avion() { delete heliceINode; delete heliceDNode; };

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

};

