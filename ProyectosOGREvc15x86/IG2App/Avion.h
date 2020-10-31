#pragma once
#include "AspasMolino.h"

class Avion : public EntidadIG
{
private:

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

