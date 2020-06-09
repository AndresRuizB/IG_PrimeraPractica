#include "Entity.h"


#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::update()
{
}

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Poligono::Poligono(GLuint numL, GLdouble rd) : Abs_Entity()
{
	mMesh = Mesh::generaPoligono(numL, rd);
}
//-------------------------------------------------------------------------

Poligono::~Poligono()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Poligono::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();
		glColor3d(1, 1, 1);
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Sierpinsky::Sierpinsky(GLuint numP, GLdouble rd) : Abs_Entity()
{
	mMesh = Mesh::generaSierpinsky(rd, numP);
}
//-------------------------------------------------------------------------

Sierpinsky::~Sierpinsky()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Sierpinsky::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPointSize(0.1);
		glColor4dv(value_ptr(mColor));
		mMesh->render();
		glColor3d(1, 1, 1);
	}
}
//-------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLdouble rd) : Abs_Entity()
{
	mMesh = Mesh::generaTrianguloRGB(rd);
}
//-------------------------------------------------------------------------

TrianguloRGB::~TrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void TrianguloRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3d(1, 1, 1);
	}
}

//-------------------------------------------------------------------------

void TrianguloRGB::update()	//la animacion del triangulo
{
	GLdouble radiusTranslation = 300, speedRotation = 8.0, speedTranslation = 4.0;

	dmat4 mI = dmat4(1);	//matriz unidad
	dmat4 rMat = rotate(mI, radians(speedRotation*frame), dvec3(0.0, 0.0, 1.0));
	dmat4 tMat = translate(mI, dvec3(cos(radians(speedTranslation *frame))* radiusTranslation,
									 sin(radians(speedTranslation *frame))* radiusTranslation, 0.0));

	setModelMat( tMat* rMat* mI);
	frame++;
}

//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloRGB(w,h);
}
//-------------------------------------------------------------------------

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void RectanguloRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glPolygonMode(GL_BACK, GL_POINT);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3d(1, 1, 1);
	}
}

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
}

Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		const dmat4 mModelMat2 = rotate(modelMat(), radians(180.0), dvec3(1.0, 0.0, 0.0));
		aMat = modelViewMat * mModelMat2;
		upload(aMat);
		mMesh->render();
		mTexture->unbind();
		glColor3d(1, 1, 1);
	}
}

void Estrella3D::update()
{
	GLdouble speedRotation = 4.0;
	dmat4 mI = dmat4(1);	//matriz unidad
	dmat4 rMat = rotate(mI, radians(speedRotation * frame), dvec3(0.0, 0.0, 1.0));
	dmat4 rMat2 = rotate(mI, radians(speedRotation/2 * frame), dvec3(0.0, 1.0, 0.0));
	dmat4 tMat = translate(mI, dvec3(-70 / 2, 70*2, -70 / 2));
	setModelMat(tMat * rMat2 * rMat * mI);
	frame++;
}

Caja::Caja(GLdouble ld) : Abs_Entity()
{
	mMesh = Mesh::generaCajaTexCor(ld);
	mMesh2 = Mesh::generaRectanguloTexCor(ld,ld,1,1);

	dmat4 mI = dmat4(1);	//matriz unidad
	dmat4 rMat = rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0));
	dmat4 tMat = translate(mI, dvec3(0, -50, 0));

	setModelMat2(tMat * rMat * mI);
}

Caja::~Caja()
{
	delete mMesh; mMesh = nullptr;
	delete mMesh2; mMesh2 = nullptr;
}

void Caja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		glCullFace(GL_FRONT);
		mTexture2->bind(GL_REPLACE);
		mMesh->render();

		//Fondo de caja
		aMat = modelViewMat * mModelMat2;
		upload(aMat);
		glCullFace(GL_BACK);
		mTexture->bind(GL_REPLACE);
		mMesh2->render();
		glCullFace(GL_FRONT);
		mTexture2->bind(GL_REPLACE);
		mMesh2->render();

		mTexture->unbind();
		mTexture2->unbind();
		glCullFace(GL_BACK / GL_FRONT);
		glDisable(GL_CULL_FACE);
		glColor3d(1, 1, 1);
	}
}

Suelo::Suelo(GLdouble w, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloTexCor(w,h,10,10);

	dmat4 mI = dmat4(1);	//matriz unidad
	dmat4 rMat = rotate(mI,radians(90.0),dvec3(1.0,0.0,0.0));

	setModelMat(rMat * mI);
}

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
}

void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
		glColor3d(1, 1, 1);
	}
}

Foto::Foto(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
	dmat4 mI = dmat4(1);	//matriz unidad
	dmat4 rMat = rotate(mI, radians(-90.0), dvec3(1.0, 0.0, 0.0));

	setModelMat(rMat * mI);
}

Foto::~Foto()
{
	delete mMesh; mMesh = nullptr;
}

void Foto::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
		glColor3d(1, 1, 1);
	}
}

void Foto::update()
{
	mTexture->loadColorBuffer();
}

Cristalera::Cristalera(GLdouble ld)
{
	mMesh = Mesh::generaCajaTexCor(ld);
}

Cristalera::~Cristalera()
{
	delete mMesh; mMesh = nullptr;
}

void Cristalera::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glColor3d(1, 1, 1);
	}
}

Planta::Planta(GLdouble ld)
{
	mMesh = Mesh::generaRectanguloTexCor(ld,ld,1,1);
}

Planta::~Planta()
{
	delete mMesh; mMesh = nullptr;
}

void Planta::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		mTexture->bind(GL_REPLACE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mMesh->render();

		const dmat4 mModelMat2 = rotate(modelMat(), radians(90.0), dvec3(0.0, 1.0, 0.0));
		aMat = modelViewMat * mModelMat2;
		upload(aMat);
		mMesh->render();

		mTexture->unbind();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glColor3d(1, 1, 1);
	}
}
