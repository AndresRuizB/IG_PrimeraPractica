//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"

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

	void setActiveLight0(bool b) { activeLight0 = b; };
	void setActiveLight1(bool b) { activeLight1 = b; };
private:
	bool activeLight0 = true;
	bool activeLight1 = true;
protected: 
	void free();
	void setGL();
	void resetGL();

	int mId = 0;

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures; //Textures
	Texture* textFoto;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

