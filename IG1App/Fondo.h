#pragma once


#include <GL/freeglut.h>
#include <glm.hpp>
#include <iostream>
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

class IG1App;

class Fondo
{
	public:
	Fondo() ;
	~Fondo();

	void setSizeVP(int xw, int yh);
	void render() const;

private:
	Mesh* rectMesh = nullptr;
	Texture* text = nullptr;
	Viewport* mViewPort = nullptr;
	Camera* mCamera = nullptr;
};

