#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <string>
#include "Aspa.h"
#include "AspasMolino.h"

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{

	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	else if (evt.keysym.sym == SDLK_g) {
		if (mSceneIndex == 3) giraMolino();
		else if (mSceneIndex == 2 || mSceneIndex == 6) mSpikesComplete->roll(Ogre::Degree(2));
	}
	else if (evt.keysym.sym == SDLK_h) {
		if (mSceneIndex == 2)mClockComplete->roll(Ogre::Degree(2));
		else if (mSceneIndex == 6) {
			mSecondsSpikeNode->translate(-240, 0, 0, Ogre::Node::TS_LOCAL);
			mSecondsSpikeNode->roll(Ogre::Degree(-1), Ogre::Node::TS_WORLD);
			mSecondsSpikeNode->translate(240, 0, 0, Ogre::Node::TS_LOCAL);
		}
	}
	else if (evt.keysym.sym == SDLK_j) {
		if (mSceneIndex == 7 || mSceneIndex == 8) {
			mTierraNode->translate(-300, 0, 0, Ogre::Node::TS_LOCAL);
			mTierraNode->yaw(Ogre::Degree(-2), Ogre::Node::TS_WORLD);
			mTierraNode->translate(300, 0, 0, Ogre::Node::TS_LOCAL);
		}
		if(mSceneIndex == 8){
			mLunaNode->translate(-250, 0, 0, Ogre::Node::TS_LOCAL);
			mLunaNode->yaw(Ogre::Degree(5), Ogre::Node::TS_WORLD);
			mLunaNode->translate(250, 0, 0, Ogre::Node::TS_LOCAL);
		}
	}


	//else if (evt.keysym.sym >= 48 && evt.keysym.sym <= 57) {
	//	mSceneIndex = evt.keysym.sym - 48;
	//}
	//else if (evt.keysym.sym == SDLK_???)

	return true;
}

void IG2App::giraMolino()
{
	mAspasNode->roll(Degree(2));

	for (int i = 0; i < nAspas; i++) {
		mSM->getSceneNode("nAdorno" + std::to_string(i))->roll(Degree(-2));
	}
}

void IG2App::shutdown()
{
	mShaderGenerator->removeSceneManager(mSM);
	mSM->removeRenderQueueListener(mOverlaySystem);

	mRoot->destroySceneManager(mSM);

	delete mTrayMgr;  mTrayMgr = nullptr;
	delete mCamMgr; mCamMgr = nullptr;

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
	// do not forget to call the base first
	IG2ApplicationContext::setup();

	mSM = mRoot->createSceneManager();

	// register our scene with the RTSS
	mShaderGenerator->addSceneManager(mSM);

	mSM->addRenderQueueListener(mOverlaySystem);

	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	addInputListener(mTrayMgr);

	addInputListener(this);
	setupScene();
}

void IG2App::setupScene(void)
{
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.6, 0.7, 0.8));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -0.5, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	// finally something to render

	if (mSceneIndex == 0) {

		Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
		Ogre::Entity* col = mSM->createEntity("Columns.mesh");
		Ogre::Entity* bathL = mSM->createEntity("RomanBathLower.mesh");
		Ogre::Entity* bathU = mSM->createEntity("RomanBathUpper.mesh");

		mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
		mSinbadNode->attachObject(ent);

		mColumnsNode = mSM->getRootSceneNode()->createChildSceneNode("nColumns");
		mColumnsNode->attachObject(col);
		mColumnsNode->attachObject(bathL);
		mColumnsNode->attachObject(bathU);

		mSinbadNode->setPosition(0, 120, -300);
		mSinbadNode->setScale(20, 20, 20);
	}
	else if (mSceneIndex == 1) {

		mClockNode = mSM->getRootSceneNode()->createChildSceneNode("nClock");
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
		int radio = 800;

		for (int i = 0; i < 12; i++) {
			mhourNode[i] = mClockNode->createChildSceneNode()->createChildSceneNode("nHora" + std::to_string(i));
			mhourNode[i]->attachObject(sphere);
			sphere = mSM->createEntity("sphere.mesh");/*
			mhourNode[i]->setPosition(Ogre::Math::Cos(360 * i * radio), Ogre::Math::Sin(360 * i * radio), 0);*/
			double ang = (2 * Ogre::Math::PI / 12) * i;
			mhourNode[i]->setPosition(Ogre::Math::Cos(ang) * radio, Ogre::Math::Sin(ang) * radio, 0);
		}

		Ogre::SceneNode* temNode = nullptr;

		for (int i = 0; i < 12; i += 2) {
			temNode = mSM->getSceneNode("nHora" + std::to_string(i));
			temNode->setScale(0.5, 0.5, 0.5);
		}

	}
	else if (mSceneIndex == 2) {

		mClockComplete = mSM->getRootSceneNode()->createChildSceneNode("nClock");

		mClockNode = mClockComplete->createChildSceneNode("nSpheresClock");
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
		int radio = 800;

		for (int i = 0; i < 12; i++) {
			mhourNode[i] = mClockNode->createChildSceneNode()->createChildSceneNode("nHora" + std::to_string(i));
			mhourNode[i]->attachObject(sphere);
			sphere = mSM->createEntity("sphere.mesh");/*
			mhourNode[i]->setPosition(Ogre::Math::Cos(360 * i * radio), Ogre::Math::Sin(360 * i * radio), 0);*/
			double ang = (2 * Ogre::Math::PI / 12) * i;
			mhourNode[i]->setPosition(Ogre::Math::Cos(ang) * radio, Ogre::Math::Sin(ang) * radio, 0);
		}

		mSpikesComplete = mClockComplete->createChildSceneNode("nClockComplete");

		Ogre::Entity* hours = mSM->createEntity("cube.mesh");
		mHoursSpikeNode = mSpikesComplete->createChildSceneNode("nHoursSpike");
		mHoursSpikeNode->attachObject(hours);
		mHoursSpikeNode->setPosition(250, 0, 0);
		mHoursSpikeNode->setScale(5.5, 0.3, 0.3);

		Ogre::Entity* minutes = mSM->createEntity("cube.mesh");
		mMinutesSpikeNode = mSpikesComplete->createChildSceneNode("nMinutesSpike");
		mMinutesSpikeNode->attachObject(minutes);
		mMinutesSpikeNode->roll((Radian)(Ogre::Math::PI / 2));
		mMinutesSpikeNode->setPosition(0, 280, 0);
		mMinutesSpikeNode->setScale(6.5, 0.2, 0.2);

		Ogre::Entity* seconds = mSM->createEntity("cube.mesh");
		mSecondsSpikeNode = mSpikesComplete->createChildSceneNode("nSecondsSpike");
		mSecondsSpikeNode->attachObject(seconds);
		mSecondsSpikeNode->roll((Radian)(Ogre::Math::PI / 2));
		mSecondsSpikeNode->setPosition(0, -280, 10);
		mSecondsSpikeNode->setScale(5.5, 0.1, 0.1);
	}
	else if (mSceneIndex == 3) {

		mAspasNode = mSM->getRootSceneNode()->createChildSceneNode("nAspas");

		nAspas = 12;
		int radio = 100;

		for (int i = 0; i < nAspas; i++) {
			mAspaNode = mAspasNode->createChildSceneNode("nAspa" + std::to_string(i));

			mTableroNode = mAspaNode->createChildSceneNode("nTablero" + std::to_string(i));
			Ogre::Entity* cubo = mSM->createEntity("cube.mesh");
			mTableroNode->attachObject(cubo);
			mTableroNode->setScale(3, 0.6, 0.25);
			mTableroNode->setPosition(130, 0, 0);

			Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
			mCilindroNode = mAspaNode->createChildSceneNode("nAdorno" + std::to_string(i));
			mCilindroNode->attachObject(cilindro);
			mCilindroNode->setScale(7, 12, 7);
			mCilindroNode->translate(250, 0, 20);

			Ogre::Degree ang = Ogre::Degree(360 / nAspas * i);

			mCilindroNode->roll(-ang);

			mAspaNode->roll(ang);

		}

	}
	else if (mSceneIndex == 4) {

		/*aspasMolino = new AspasMolino(5, mSM->getRootSceneNode(), mSM);
		addInputListener(aspasMolino);*/
	}
	else if (mSceneIndex == 5) {
		Molino* a = new Molino(mSM);
		addInputListener(a);
	}
	else if (mSceneIndex == 6) {
		mClockComplete = mSM->getRootSceneNode()->createChildSceneNode("nClock");

		mClockNode = mClockComplete->createChildSceneNode("nSpheresClock");
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
		int radio = 800;

		for (int i = 0; i < 12; i++) {
			mhourNode[i] = mClockNode->createChildSceneNode()->createChildSceneNode("nHora" + std::to_string(i));
			mhourNode[i]->attachObject(sphere);
			sphere = mSM->createEntity("sphere.mesh");/*
			mhourNode[i]->setPosition(Ogre::Math::Cos(360 * i * radio), Ogre::Math::Sin(360 * i * radio), 0);*/
			double ang = (2 * Ogre::Math::PI / 12) * i;
			mhourNode[i]->setPosition(Ogre::Math::Cos(ang) * radio, Ogre::Math::Sin(ang) * radio, 0);
		}

		mSpikesComplete = mClockComplete->createChildSceneNode("nClockComplete");

		Ogre::Entity* hours = mSM->createEntity("cube.mesh");
		mHoursSpikeNode = mSpikesComplete->createChildSceneNode("nHoursSpike");
		mHoursSpikeNode->attachObject(hours);
		mHoursSpikeNode->setPosition(250, 0, 0);
		mHoursSpikeNode->setScale(5.5, 0.3, 0.3);

		Ogre::Entity* minutes = mSM->createEntity("cube.mesh");
		mMinutesSpikeNode = mSpikesComplete->createChildSceneNode("nMinutesSpike");
		mMinutesSpikeNode->attachObject(minutes);
		mMinutesSpikeNode->roll((Radian)(Ogre::Math::PI / 2));
		mMinutesSpikeNode->setPosition(0, 280, 0);
		mMinutesSpikeNode->setScale(6.5, 0.2, 0.2);

		Ogre::Entity* seconds = mSM->createEntity("cube.mesh");
		mSecondsSpikeNode = mSpikesComplete->createChildSceneNode("nSecondsSpike");
		mSecondsSpikeNode->attachObject(seconds);
		mSecondsSpikeNode->roll(Ogre::Degree(225), Ogre::Node::TS_WORLD);
		mSecondsSpikeNode->translate(240, 0, 0, Ogre::Node::TS_LOCAL);
		mSecondsSpikeNode->setScale(7, 0.1, 0.1);
	}
	else if (mSceneIndex == 7) {

		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
		mSolNode = mSM->getRootSceneNode()->createChildSceneNode("nSolNode");
		mSolNode->attachObject(sphere);

		sphere = mSM->createEntity("sphere.mesh");
		mTierraNode = mSolNode->createChildSceneNode("nTierraNode");
		mTierraNode->attachObject(sphere);

		mTierraNode->translate(300, 0, 0);
		mTierraNode->setScale(0.5, 0.5, 0.5);
	}
	else if (mSceneIndex == 8) {

	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	mSolNode = mSM->getRootSceneNode()->createChildSceneNode("nSolNode");
	mSolNode->attachObject(sphere);

	sphere = mSM->createEntity("sphere.mesh");
	mTierraNode = mSolNode->createChildSceneNode("nTierraNode");
	mTierraNode->attachObject(sphere);

	mTierraNode->translate(300, 0, 0);
	mTierraNode->setScale(0.5, 0.5, 0.5);

	sphere = mSM->createEntity("sphere.mesh");
	mLunaNode = mTierraNode->createChildSceneNode("nLunaNode");
	mLunaNode->attachObject(sphere);

	mLunaNode->translate(250, 0, 0);
	mLunaNode->setScale(0.2, 0.2, 0.2);
	}
	else if (mSceneIndex == 9) {
	Avion* a = new Avion(mSM->getRootSceneNode(), mSM);
	addInputListener(a);
	}

	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}

