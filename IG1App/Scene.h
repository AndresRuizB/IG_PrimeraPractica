//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "DirLight.h"
#include "SpotLight.h"
#include "PosLight.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene
{
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment

	void init();

	void render(Camera const& cam) const;
	void update();
	void setState(int id);

	void saveCapture();

	void sceneDirLight(Camera const& cam) const;
	void scenePosLight(Camera const& cam) const;
	void sceneSpotLight(Camera const& cam) const;

	void switchDirLight(bool b) { dirLightOn = b; }
	void switchPosLight(bool b) { posLightOn = b; }
	void switchSpotLight(bool b) { spotLightOn = b; }
	void switchAllLights() {
		allLightOn = !allLightOn; dirLightOn = false; posLightOn = false; spotLightOn = false; planeSpotLightOn = false;
	}

	void switchPlaneLight(bool b) { planeSpotLightOn = b; };
	void switchMinerLight(bool b) { mineroLightOn = b; };

	void move();

protected:
	void free();
	void setGL();
	void resetGL();
	void setLights();
	void updateLights(Camera const& cam) const;

	int mId = 0;

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures; //Textures
	Texture* textFoto;
	DirLight* directionalLight;
	bool dirLightOn;
	PosLight* positionalLight;
	bool posLightOn;
	SpotLight* spotSceneLight;
	bool spotLightOn;
	DirLight* mineroLight;
	bool mineroLightOn;

	SpotLight* planeSpotLight;
	bool planeSpotLightOn;

	bool allLightOn = true;

	CompoundEntity* avion;
	CompoundEntity* helices;
	int frame = 0;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

