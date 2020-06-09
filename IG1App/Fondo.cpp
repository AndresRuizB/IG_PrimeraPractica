#include "Fondo.h"
#include "Mesh.h"

#include <gtc/type_ptr.hpp>

#include"IG1App.h"

using namespace std;
using namespace glm;

Fondo::Fondo() {
	rectMesh = new Mesh();
	rectMesh= Mesh::generaRectanguloTexCor(2,2, 1, 1);

	mViewPort = new Viewport(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight());
	mCamera = new Camera(mViewPort);
	mCamera->setSize(2,2);

	mCamera->set2D();

	text = new Texture();
	text->load("../Bmps/noche.bmp");
}

Fondo::~Fondo()
{
	delete rectMesh; rectMesh = nullptr;
	delete mViewPort; mViewPort = nullptr;
	delete mCamera; mCamera = nullptr;
	delete text; text = nullptr;
}

void Fondo::setSizeVP(int xw, int yh)
{
	mViewPort->setSize(xw, yh);
}

void Fondo::render() const
{
	mCamera->upload();

	if (rectMesh != nullptr) {
		glDisable(GL_DEPTH_TEST);
		text->bind(GL_REPLACE);
		rectMesh->render();

		glEnable(GL_DEPTH_TEST);
		text->unbind();
	}
}
