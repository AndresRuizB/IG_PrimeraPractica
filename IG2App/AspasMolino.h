#pragma once
#include "EntidadIG.h"
#include "Aspa.h"

class AspasMolino : public EntidadIG
{
private:
	Ogre::SceneNode* cilindroCentral;
	Aspa** arrayAspas;
	int numAspas;


	void mueveCentro();

public:
	AspasMolino(int numA, Ogre::SceneNode* parent);
	AspasMolino(int numA, Ogre::SceneNode* parent,  int index);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void frameRendered(const Ogre::FrameEvent& evt);
	void giraMolino();
};

