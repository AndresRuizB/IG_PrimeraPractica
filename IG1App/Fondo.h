#pragma once

#include "GLinclude.h"
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
	Texture* text2 = nullptr; // EXTRA 2
	Viewport* mViewPort = nullptr;
	Camera* mCamera = nullptr;

};

