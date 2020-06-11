#include "Fondo.h"
#include "Mesh.h"

#include <gtc/type_ptr.hpp>

#include"IG1App.h"

using namespace std;
using namespace glm;

Fondo::Fondo() {
	rectMesh = Mesh::generaRectanguloTexCor(2,2, 1, 1);
	rectMesh->setTwoUnits(); // EXTRA 2

	mViewPort = new Viewport(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight());
	mCamera = new Camera(mViewPort);
	mCamera->setSize(2,2);

	mCamera->set2D();

	text = new Texture();
	text->load("../Bmps/noche.bmp");


	text2 = new Texture(); // EXTRA 2
	text2->load("../Bmps/Zelda.bmp", 70); // EXTRA 2

}

Fondo::~Fondo()
{
	delete rectMesh; rectMesh = nullptr;
	delete mViewPort; mViewPort = nullptr;
	delete mCamera; mCamera = nullptr;
	delete text; text = nullptr;
	delete text2; text2 = nullptr; // EXTRA 2
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

		text->bind(GL_TEXTURE0, GL_REPLACE); // EXTRA 2
		text2->bind(GL_TEXTURE1, GL_DECAL); // EXTRA 2

		rectMesh->render();

		glEnable(GL_DEPTH_TEST);
		text->unbind(GL_TEXTURE0); // EXTRA 2
		text2->unbind(GL_TEXTURE1); // EXTRA 2
	}
}
