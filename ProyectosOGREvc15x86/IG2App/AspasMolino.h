#pragma once
#include "Aspa.h"

class AspasMolino : public EntidadIG
{
private:
	Ogre::SceneNode* centroNode;
	Aspa** arrayAspas;
	int numAspas;

	void giraMolino();

public:
	AspasMolino(int numA, Ogre::SceneNode* node);
	/*Constructora para el avion*/
	AspasMolino(int numA,int numAspasScene, Ogre::SceneNode* node);
	~AspasMolino();
	void orbitaMolino();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

