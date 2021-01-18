#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreMovablePlane.h>
#include <OgreTexture.h>
#include <OgreTextureManager.h>
#include <OgreRenderTexture.h>

#include "Molino.h"
#include "Avion.h"
#include "Plano.h"
#include "Simbad.h"
#include "Boya.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  virtual void windowResized(Ogre::RenderWindow* rw);

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
  
  virtual void giraMolino();

  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;

  Ogre::SceneNode* mSinbadNode = nullptr;
  Ogre::SceneNode* mColumnsNode = nullptr;

  OgreBites::CameraMan* mCamMgr = nullptr;

  Ogre::SceneNode* mhourNode[12];
  Ogre::SceneNode* mSpheresClockNode = nullptr;
  Ogre::SceneNode* mHoursSpikeNode = nullptr;
  Ogre::SceneNode* mMinutesSpikeNode = nullptr;
  Ogre::SceneNode* mSecondsSpikeNode = nullptr;
  Ogre::SceneNode* mSpikesComplete = nullptr;
  Ogre::SceneNode* mClockComplete = nullptr;

  Ogre::SceneNode* mAspaNode = nullptr;
  Ogre::SceneNode* mTableroNode = nullptr;
  Ogre::SceneNode* mCilindroNode = nullptr;
  Ogre::SceneNode* mAspasNode = nullptr;
  int nAspas;

  Ogre::SceneNode* mSolNode = nullptr;
  Ogre::SceneNode* mTierraNode = nullptr;
  Ogre::SceneNode* mLunaNode = nullptr;

  //AspasMolino* aspasMolino = nullptr;
  Molino* molino = nullptr;
  Avion* avion = nullptr;
  Plano* plano = nullptr;
  Plano* plano2 = nullptr;
  Plano* plano3 = nullptr;
  Simbad* simbad = nullptr;
  Boya* boya = nullptr;

  Ogre::Camera* camRef = nullptr;

  bool luminActive = true;
  bool edgeActive = true;

  int mSceneIndex = 10;

};

#endif
