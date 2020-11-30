#include "Simbad.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

void Simbad::createAnimWalk()
{
	Ogre::Real duracion = 12;
	Ogre::Animation* animation = mSM->createAnimation("simbadWalk", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	animation->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);
	track->setAssociatedNode(mNode);

	Ogre::Vector3 keyframePos(0., 0., 0.); // posición inicial
	Ogre::Vector3 src(1, 0, 0); // orientación inicial
	Ogre::Real durPaso = duracion / 6.0; // uniformes
	long longDesplazamiento = 50; // desplazamiento

	Ogre::TransformKeyFrame* kf; // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
	kf->setTranslate(keyframePos); // Origen: Vector3

	kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 1: abajo
	keyframePos += Ogre::Vector3(350, 0, -230);
	kf->setTranslate(keyframePos); // Abajo
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 0))); // Yaw(45)

	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 2: arriba
	//keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
	kf->setTranslate(keyframePos); // Arriba
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 0))); // Yaw(180)

	kf = track->createNodeKeyFrame(durPaso * 5); // Keyframe 3: origen
	keyframePos += Ogre::Vector3(-350, 0, 230);
	kf->setTranslate(keyframePos); // Origen
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 0))); // Yaw(180)

	kf = track->createNodeKeyFrame(durPaso * 6); // Keyframe 3: origen
	kf->setTranslate(keyframePos); // Origen
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 0))); // Yaw(180)
}

Simbad::Simbad(Ogre::SceneNode* node) : EntidadIG(node)
{
	alternateAnimation = true;
	alternateSword = true;
	walking = false;

	simbadEntity = mSM->createEntity("Sinbad.mesh");
	swordEntity = mSM->createEntity("Sword.mesh");
	mNode->attachObject(simbadEntity);
	simbadEntity->attachObjectToBone("Handle.R", swordEntity);

	mNode->setInitialState();

	createAnimWalk();

	animationStateDance = simbadEntity->getAnimationState("Dance");
	animationStateRunT = simbadEntity->getAnimationState("RunTop");
	animationStateRunB = simbadEntity->getAnimationState("RunBase");
	animationStateWalk = mSM->createAnimationState("simbadWalk");

	animationStateDance->setEnabled(true);
	animationStateRunT->setEnabled(false);
	animationStateRunB->setEnabled(false);
	animationStateWalk->setEnabled(false);

	animationStateDance->setLoop(true);
	animationStateRunT->setLoop(true);
	animationStateRunB->setLoop(true);
	animationStateWalk->setLoop(true);
}

bool Simbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_c) {
		alternateAnimation = !alternateAnimation;
		animationStateDance->setEnabled(alternateAnimation);
		animationStateRunT->setEnabled(!alternateAnimation);
		animationStateRunB->setEnabled(!alternateAnimation);

		animationStateDance->setTimePosition(0);
		animationStateRunT->setTimePosition(0);
		animationStateRunB->setTimePosition(0);
	}
	else if (evt.keysym.sym == SDLK_e) {
		alternateSword = !alternateSword;
		simbadEntity->detachObjectFromBone(swordEntity);
		if (alternateSword) simbadEntity->attachObjectToBone("Handle.R", swordEntity);
		else simbadEntity->attachObjectToBone("Handle.L", swordEntity);
	}
	else if (evt.keysym.sym == SDLK_w) {
		walking = !walking;
		simbadEntity->detachObjectFromBone(swordEntity);
		simbadEntity->attachObjectToBone("Handle.R", swordEntity);
		animationStateDance->setEnabled(!walking);
		animationStateRunB->setEnabled(walking);
		animationStateRunT->setEnabled(walking);
		animationStateWalk->setEnabled(walking);
	}
	return false;
}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	animationStateDance->addTime(evt.timeSinceLastFrame);
	animationStateRunT->addTime(evt.timeSinceLastFrame);
	animationStateRunB->addTime(evt.timeSinceLastFrame);
	if (walking) animationStateWalk->addTime(evt.timeSinceLastFrame);
}
