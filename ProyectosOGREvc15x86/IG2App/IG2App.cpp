#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <string>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{

	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	else if (evt.keysym.sym == SDLK_g) {
		if (mSceneIndex == 3) giraMolino();
		else if (mSceneIndex == 6) mClockComplete->roll(Ogre::Degree(2));
	}
	else if (evt.keysym.sym == SDLK_h) {
		if (mSceneIndex == 6) {
			//mSpheresClockNode->roll(Ogre::Degree(2));
			mSecondsSpikeNode->translate(-80, 0, 0, Ogre::Node::TS_LOCAL);
			mSecondsSpikeNode->roll(Ogre::Degree(-1), Ogre::Node::TS_PARENT);
			mSecondsSpikeNode->translate(80, 0, 0, Ogre::Node::TS_LOCAL);
		}

	}
	else if (evt.keysym.sym == SDLK_j) {
		if (mSceneIndex == 7) {
			mTierraNode->translate(0, 0, -200, Ogre::Node::TS_LOCAL);
			mTierraNode->yaw(Ogre::Degree(-2));
			mTierraNode->translate(0, 0, 200, Ogre::Node::TS_LOCAL);

			mLunaNode->translate(150, 0, 0, Ogre::Node::TS_LOCAL);
			mLunaNode->yaw(Ogre::Degree(6));
			mLunaNode->translate(-150, 0, 0, Ogre::Node::TS_LOCAL);
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
	//delete aspasMolino; aspasMolino = nullptr;
	delete molino; molino = nullptr;
	delete avion; avion = nullptr;
	delete plano; plano = nullptr;
	delete plano2; plano2 = nullptr;
	delete plano3; plano3 = nullptr;
	delete simbad; simbad = nullptr;
	delete boya; boya = nullptr;

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

	//para el reflejo
	camRef = mSM->createCamera("CamRef");
	camRef->setNearClipDistance(1);
	camRef->setFarClipDistance(10000);
	camRef->setAutoAspectRatio(true);


	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->attachObject(camRef);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);


	//vp->setBackgroundColour(Ogre::ColourValue(0.6, 0.7, 0.8));
	vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));

	Ogre::RenderWindow* a = getRenderWindow();

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1.0, 1.0, 1.0);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0.0, -1.0, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);
	//mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
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

		mSpheresClockNode = mSM->getRootSceneNode()->createChildSceneNode("nClock");
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
		int radio = 800;

		for (int i = 0; i < 12; i++) {
			mhourNode[i] = mSpheresClockNode->createChildSceneNode()->createChildSceneNode("nHora" + std::to_string(i));
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

		mSpheresClockNode = mClockComplete->createChildSceneNode("nSpheresClock");
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
		int radio = 800;

		for (int i = 0; i < 12; i++) {
			mhourNode[i] = mSpheresClockNode->createChildSceneNode()->createChildSceneNode("nHora" + std::to_string(i));
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

		//aspasMolino = new AspasMolino(5, mSM->getRootSceneNode(), mSM);
		//addInputListener(aspasMolino);

	}

	//PRACTICA 1.2 ----------------------------------------------------------------------

	else if (mSceneIndex == 5) {

		Ogre::SceneNode* nodoMolino = mSM->getRootSceneNode()->createChildSceneNode("nMolino");
		molino = new Molino(nodoMolino);
		addInputListener(molino);
	}
	else if (mSceneIndex == 6) {
		mClockComplete = mSM->getRootSceneNode()->createChildSceneNode("nClock");

		mSpheresClockNode = mClockComplete->createChildSceneNode("nSpheresClock");
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
		int radio = 300;

		for (int i = 0; i < 12; i++) {
			mhourNode[i] = mSpheresClockNode->createChildSceneNode()->createChildSceneNode("nHora" + std::to_string(i));
			mhourNode[i]->attachObject(sphere);
			sphere = mSM->createEntity("sphere.mesh");
			double ang = (2 * Ogre::Math::PI / 12) * i;

			Ogre::SceneNode* mHN = mSM->getSceneNode("nHora" + std::to_string(i));
			mHN->setPosition(Ogre::Math::Cos(ang) * radio, Ogre::Math::Sin(ang) * radio, 0);
			mHN->setScale(0.3, 0.3, 0.3);
		}

		mSpikesComplete = mClockComplete->createChildSceneNode("nClockComplete");

		Ogre::Entity* hours = mSM->createEntity("cube.mesh");
		mHoursSpikeNode = mSpikesComplete->createChildSceneNode("nHoursSpike");
		mHoursSpikeNode->attachObject(hours);
		mHoursSpikeNode->translate(50, 0, 0, Ogre::Node::TS_LOCAL);
		mHoursSpikeNode->setScale(1.5, 0.3, 0.3);

		Ogre::Entity* minutes = mSM->createEntity("cube.mesh");
		mMinutesSpikeNode = mSpikesComplete->createChildSceneNode("nMinutesSpike");
		mMinutesSpikeNode->attachObject(minutes);
		mMinutesSpikeNode->roll(Ogre::Degree(90), Ogre::Node::TS_WORLD);
		mMinutesSpikeNode->translate(80, 0, 0, Ogre::Node::TS_LOCAL);
		mMinutesSpikeNode->setScale(2.5, 0.2, 0.2);

		Ogre::Entity* seconds = mSM->createEntity("cube.mesh");
		mSecondsSpikeNode = mSpikesComplete->createChildSceneNode("nSecondsSpike");
		mSecondsSpikeNode->attachObject(seconds);
		mSecondsSpikeNode->roll(Ogre::Degree(225), Ogre::Node::TS_WORLD);
		mSecondsSpikeNode->translate(80, 0, 0, Ogre::Node::TS_LOCAL);
		mSecondsSpikeNode->setScale(2.5, 0.1, 0.1);
	}
	else if (mSceneIndex == 7) {
		Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
		mSolNode = mSM->getRootSceneNode()->createChildSceneNode("nSol");
		mSolNode->attachObject(ent);

		ent = mSM->createEntity("sphere.mesh");
		mTierraNode = mSM->getRootSceneNode()->createChildSceneNode("nTierra");
		mTierraNode->attachObject(ent);
		mTierraNode->translate(0, 0, 200, Ogre::Node::TS_LOCAL);
		mTierraNode->setScale(0.5, 0.5, 0.5);

		ent = mSM->createEntity("sphere.mesh");
		mLunaNode = mTierraNode->createChildSceneNode("nLuna");
		mLunaNode->attachObject(ent);
		mLunaNode->translate(-150, 0, 0, Ogre::Node::TS_LOCAL);
		mLunaNode->setScale(0.3, 0.3, 0.3);
	}
	else if (mSceneIndex == 8) {

		Ogre::SceneNode* nodoAvion = mSM->getRootSceneNode()->createChildSceneNode("nAvion");
		avion = new Avion(nodoAvion);
		addInputListener(avion);

	}
	//------------------------------------------------------------------------

	//PRACTICA 1.3 ----------------------------------------------------------------------

	else if (mSceneIndex == 9) {
		Ogre::SceneNode* nodoMolino = mSM->getRootSceneNode()->createChildSceneNode("nMolino");
		molino = new Molino(nodoMolino);
		addInputListener(molino);
		EntidadIG::addListener(molino);

		MeshManager::getSingleton().createPlane("mPlane1080x800",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Plane(Vector3::UNIT_Y, 0),
			1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

		Ogre::SceneNode* planoNode = mSM->getRootSceneNode()->createChildSceneNode("nPlano");
		plano = new Plano(planoNode);
		EntidadIG::addListener(plano);

		planoNode->translate(0, -200, 0);
	}

	//PRACTICA 1.4 ----------------------------------------------------------------------

	else if (mSceneIndex == 10) {


		mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
		mSinbadNode->setScale(15, 15, 15);
		mSinbadNode->translate(-350, -140, 230);
		mSinbadNode->yaw(Ogre::Degree(135));
		simbad = new Simbad(mSinbadNode);
		addInputListener(simbad);
		EntidadIG::addListener(simbad);

		Ogre::SceneNode* nodoAvion = mSM->getRootSceneNode()->createChildSceneNode("nAvion");
		avion = new Avion(nodoAvion);
		addInputListener(avion);
		EntidadIG::addListener(avion);
		nodoAvion->setScale(0.3, 0.3, 0.3);
		nodoAvion->translate(-300, 500, 0);

		Ogre::SceneNode* nodoMolino = mSM->getRootSceneNode()->createChildSceneNode("nMolino");
		molino = new Molino(nodoMolino);
		addInputListener(molino);
		EntidadIG::addListener(molino);

		MeshManager::getSingleton().createPlane("mPlane1080x800",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Plane(Vector3::UNIT_Y, 0),
			1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

		Ogre::SceneNode* planoNode = mSM->getRootSceneNode()->createChildSceneNode("nPlano");
		plano = new Plano(planoNode, 1);
		EntidadIG::addListener(plano);
		planoNode->translate(0, -220, 0);

		Ogre::SceneNode* plano2Node = mSM->getRootSceneNode()->createChildSceneNode("nPlano2");
		plano2 = new Plano(plano2Node, 2);
		plano2Node->setScale(0.35, 1, 0.4);
		plano2Node->translate(-350, -215, 240);

		Ogre::SceneNode* plano3Node = mSM->getRootSceneNode()->createChildSceneNode("nPlano3");
		plano3 = new Plano(plano3Node, 3);
		plano3Node->setScale(0.4, 1, 0.4);
		plano3Node->translate(330, -210, -240);

		Ogre::SceneNode* cabezaNode = mSM->getRootSceneNode()->createChildSceneNode("nCabeza");
		cabezaNode->setScale(0.4, 0.4, 0.4);
		cabezaNode->translate(500, -170, -150);
		Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
		ent->setMaterialName("Practica1/cabeza");
		cabezaNode->attachObject(ent);

		Ogre::SceneNode* boyaNode = mSM->getRootSceneNode()->createChildSceneNode("nBoya");
		boyaNode->setScale(35, 35, 35);
		boyaNode->translate(0, -220, 0);
		boya = new Boya(boyaNode);
		addInputListener(boya);

		//mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -200), "Practica2/space", 1, 1, true, 0.0, 10, 10);

		MovablePlane* mpRef = new MovablePlane(Plane(Vector3::UNIT_Y, 0));
		planoNode->attachObject(mpRef);

		camRef->enableReflection(mpRef);
		camRef->enableCustomNearClipPlane(mpRef);

		TexturePtr rttRef = TextureManager::getSingleton().createManual(
			"rttRelejo",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			TEX_TYPE_2D,
			720,
			480,
			0, PF_R8G8B8, TU_RENDERTARGET
		);

		RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
		Ogre::Viewport* vpt = renderTexture->addViewPort();

	}

	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}

