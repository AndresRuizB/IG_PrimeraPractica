#pragma once
#include "IG2ApplicationContext.h"

#include "AspasMolino.h"
#include "EntidadIG.h"

class Molino : public EntidadIG
{
private:
	
	Ogre::SceneNode* techoNode = nullptr;
	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* aspasNode = nullptr;
	Ogre::SceneNode* auxNode = nullptr;

	AspasMolino* aspas = nullptr;

	void orbitaAspas();
public:
	Molino(Ogre::SceneNode* parent);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

