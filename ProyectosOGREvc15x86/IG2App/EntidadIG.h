#pragma once
#include "IG2ApplicationContext.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>

enum MessageType { R_KEY , C_KEY, E_KEY};

class EntidadIG : public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* node);
	~EntidadIG();
	//Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad);
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	void sendEvent(MessageType msgType, EntidadIG* entidad);
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad) {};

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt)
	{
		return false;
	};
	virtual void frameRendered(const Ogre::FrameEvent& evt) {};
};