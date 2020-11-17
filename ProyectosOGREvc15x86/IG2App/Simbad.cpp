#include "Simbad.h"
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

void Simbad::creaAnimacionCaminar()
{
	Ogre::Real duracion = 9;
	Ogre::Animation* animation = mSM->createAnimation("SimbadWalk", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	mNode->setInitialState();

	Ogre::Vector3 keyframePos(0., 0., 0.);	//Estado inicial
	Ogre::Vector3 src(0, 0, 1);
	Ogre::Real durPaso = duracion / 5.0; // uniformes
	long longDesplazamiento = 300; // desplazamiento

	Ogre::TransformKeyFrame* kf; // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
	kf->setTranslate(keyframePos);	//Inicio

	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: mirando hacia la boya
	kf->setTranslate(keyframePos); 
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, -1))); 

	kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: en la boya
	keyframePos += Ogre::Vector3(1, 0, -1) * longDesplazamiento;
	kf->setTranslate(keyframePos); 
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, -1))); 

	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: en la boya mirando hacia el origen
	kf->setTranslate(keyframePos); 
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1))); 

	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: en el origen
	keyframePos += Ogre::Vector3(-1, 0, 1) * longDesplazamiento;
	kf->setTranslate(keyframePos); 
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1))); 

	kf = track->createNodeKeyFrame(durPaso * 5); // Keyframe 4: en el origen
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0, 0, 1)));

	animWalk = mSM->createAnimationState("SimbadWalk");
	animWalk->setLoop(true);
	animWalk->setEnabled(true);

	animTop->setEnabled(true);
	animBot->setEnabled(true);
}

Simbad::Simbad(Ogre::SceneNode* node) : EntidadIG(node)
{
	ent = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(ent);
	mNode->setScale(15, 15, 15);
	mNode->translate(-350, -140, 230);

	espada = mSM->createEntity("Sword.mesh");

	animDance = ent->getAnimationState("Dance");
	animDance->setEnabled(false);
	animDance->setLoop(false);
	animTop = ent->getAnimationState("RunTop");
	animTop->setEnabled(false);
	animTop->setLoop(false);
	animBot = ent->getAnimationState("RunBase");
	animBot->setEnabled(false);
	animBot->setLoop(false);

	creaAnimacionCaminar();
}

Simbad::~Simbad()
{
}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if (sinbadEstaBailando) {
		animDance->setEnabled(true);
		animTop->setEnabled(false);
		animBot->setEnabled(false);

		animDance->addTime(evt.timeSinceLastFrame);

		if (animDance->hasEnded()) animDance->setTimePosition(0);
	}
	else {
		animDance->setEnabled(false);
		animTop->setEnabled(true);
		animBot->setEnabled(true);

		animTop->addTime(evt.timeSinceLastFrame);
		animBot->addTime(evt.timeSinceLastFrame);

		if (animTop->hasEnded()) animTop->setTimePosition(0);
		if (animBot->hasEnded()) animBot->setTimePosition(0);
	}

	animWalk->addTime(evt.timeSinceLastFrame);

}

void Simbad::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	switch (msgType)
	{
	case C_KEY:
		sinbadEstaBailando = !sinbadEstaBailando;
		break;
	case E_KEY:

		espadaEnManoDer = !espadaEnManoDer;
		ent->detachAllObjectsFromBone();

		if (espadaEnManoDer) ent->attachObjectToBone("Handle.R", espada);
		else ent->attachObjectToBone("Handle.L", espada);

		break;
	default:
		break;
	}

}