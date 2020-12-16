#include "Boya.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>


Boya::Boya(Ogre::SceneNode* node) : EntidadIG(node)
{
	Ogre::Entity* e = mSM->createEntity("uv_sphere.mesh");
	e->setMaterialName("IG2/agujeroGLSL");
	mNode->attachObject(e);
	float scale = 0.3;
	mNode->setScale(scale,scale,scale);
	mNode->setInitialState();

	Ogre::Real duracion = 8;
	Ogre::Animation* animation = mSM->createAnimation("animVV", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	animation->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);
	track->setAssociatedNode(mNode);

	Ogre::Vector3 keyframePos(0., 0., 0.); // posición inicial
	Ogre::Vector3 src(0, 0, 1); // orientación inicial
	Ogre::Real durPaso = duracion / 4.0; // uniformes
	long longDesplazamiento = 20; // desplazamiento

	Ogre::TransformKeyFrame* kf; // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
	kf->setTranslate(keyframePos); // Origen: Vector3

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
	kf->setTranslate(keyframePos); // Origen


	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
	
}

void Boya::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}
