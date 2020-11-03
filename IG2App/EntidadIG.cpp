#include "EntidadIG.h"
#include <OgreSceneNode.h>

// Inicialización del vector de listeners
std::vector<EntidadIG*> EntidadIG::appListeners =
std::vector<EntidadIG*>(0, nullptr);
EntidadIG::EntidadIG(Ogre::SceneNode* nodo) {
	mNode = nodo;
	mSM = mNode->getCreator();
}
EntidadIG::~EntidadIG() {

}

void EntidadIG::addListener(EntidadIG* entidad)
{
	appListeners.push_back(entidad);
}

void EntidadIG::sendEvent(MessageType msgType, EntidadIG* entidad)
{
	for (EntidadIG* e : appListeners)
		e->receiveEvent(msgType, this);
}
