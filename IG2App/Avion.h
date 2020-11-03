#pragma once
#include "AspasMolino.h"
#include "EntidadIG.h"

class Avion :public EntidadIG
{
private:


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

	Avion(Ogre::SceneNode* parent);
	~Avion();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

