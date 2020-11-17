#include "Boya.h"
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

Boya::Boya(Ogre::SceneNode* node) : EntidadIG(node)
{
	Ogre::Entity* e = mSM->createEntity("Barrel.mesh");
	e->setMaterialName("boya");
	mNode->attachObject(e);
	mNode->setScale(18, 18, 18);
	mNode->setInitialState();

	Ogre::Real duracion = 9;
	Ogre::Animation* animation = mSM->createAnimation("animVV", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	animation->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);

	Ogre::Vector3 keyframePos(0., -200.0, 0.);	//Estado inicial
	Ogre::Vector3 src(0, 0, 1);
	Ogre::Real durPaso = duracion / 4.0; // uniformes
	long longDesplazamiento = 25; // desplazamiento

	Ogre::TransformKeyFrame* kf; // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
	kf->setTranslate(keyframePos);	//Inicio

	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: abajo
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Abajo
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 1))); // Yaw(45)

	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 2: arriba
	keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
	kf->setTranslate(keyframePos); // Arriba
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1))); // Yaw(-45)

	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 3: origen
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); //Inicio

	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

Boya::~Boya()
{
}

void Boya::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}
