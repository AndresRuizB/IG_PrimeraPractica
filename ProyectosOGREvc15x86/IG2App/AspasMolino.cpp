#include "AspasMolino.h"
#include <SDL_keycode.h>
#include "IG2App.h"

AspasMolino::AspasMolino(Ogre::SceneNode* node, int nAspas)
{
	//La constructora pasa el nodo asociado al objeto
	//creado, como parámetro
	aspasNode = node;

	numAspas = nAspas;
	arrayAspas = new Aspa* [numAspas];

	for (int i = 0; i < numAspas; i++) {

		Ogre::SceneNode* aspaNode = aspasNode->createChildSceneNode("aspa_" + std::to_string(i + 1));

		Ogre::SceneNode* tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(i + 1));

		Ogre::SceneNode* cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(i + 1));

		arrayAspas[i] = new Aspa(aspaNode, tableroNode, cilindroNode);

		tableroNode->setPosition(Ogre::Math::Cos(Ogre::Math::DegreesToRadians(i * 30)) * 50, Ogre::Math::Sin(Ogre::Math::DegreesToRadians(i * 30)) * 50, 0);
		tableroNode->roll(Ogre::Degree(i * 30));

		cilindroNode->setPosition(Ogre::Math::Cos(Ogre::Math::DegreesToRadians(i * 30)) * 230, Ogre::Math::Sin(Ogre::Math::DegreesToRadians(i * 30)) * 230, 0);

	}
}

AspasMolino::~AspasMolino()
{
	for (int i = 0; i < numAspas;i++) {
		delete arrayAspas[i];
	}
	delete[] arrayAspas;
	arrayAspas = nullptr;
}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) // #include <SDL_keycode.h>
	{
		aspasNode->roll(Ogre::Degree(5));
		for (int i = 0; i < numAspas; i++) {
			arrayAspas[i]->keyPressed(evt);
		}
	}
	return true;
}
