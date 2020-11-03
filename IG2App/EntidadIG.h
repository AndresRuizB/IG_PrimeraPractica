#pragma once
#include "IG2ApplicationContext.h"

enum MessageType { };

class EntidadIG :
	public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* node);

	~EntidadIG();
	//Vector est�tico de listeners
	static std::vector<EntidadIG*> appListeners;
	//A�adir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad);
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt)
	{
		return false;
	};

	void sendEvent(MessageType msgType, EntidadIG* entidad);
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad) {};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {};
};

