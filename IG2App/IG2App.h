#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "AspasMolino.h"
#include "Molino.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

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
  Ogre::SceneNode* mClockNode = nullptr;
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

  AspasMolino* aspasMolino = nullptr;

  Molino* molino = nullptr;
  
  int mSceneIndex = 6;

};

#endif
