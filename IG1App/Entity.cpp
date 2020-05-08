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

EjesRGB::EjesRGB(GLdouble l) : Abs_Entity()
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
		glPointSize(1);
		glColor4dv(value_ptr(mColor));
		mMesh->render();
		glColor3d(1, 1, 1);
		glPointSize(1);
	}
}
//-------------------------------------------------------------------------
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
	dmat4 rMat = rotate(mI, radians(speedRotation * frame), dvec3(0.0, 0.0, 1.0));
	dmat4 tMat = translate(mI, dvec3(cos(radians(speedTranslation * frame)) * radiusTranslation,
		sin(radians(speedTranslation * frame)) * radiusTranslation, 0.0));

	setModelMat(tMat * rMat * mI);
	frame++;
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloRGB(w, h);
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
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Estrella3D::Estrella3D(GLdouble re, GLdouble ri, GLdouble np, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaEstrella3D(re, ri, np, h);
}
//-------------------------------------------------------------------------

Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Estrella3D::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		dmat4 mI = dmat4(1);
		dmat4 rMat = rotate(mI, radians(180.0), dvec3(0.0, 1.0, 0.0));
		aMat = modelViewMat * mModelMat * rMat;
		upload(aMat);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3d(1, 1, 1);
	}
}
//-------------------------------------------------------------------------

void Estrella3D::update()	//la animacion de la estrella
{
	GLdouble radiusTranslation = 300, speedRotation = 4.0, speedTranslation = 4.0;

	dmat4 mI = dmat4(1);	//matriz unidad
	dmat4 rMat = rotate(mI, radians(speedRotation * frame), dvec3(0.0, 1.0, 0.9));

	setModelMat(rMat * mI);
	frame++;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Caja::Caja(GLdouble ld) : Abs_Entity()
{
	mMesh = Mesh::generaContCubo(ld);
}
//-------------------------------------------------------------------------

Caja::~Caja()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Caja::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3d(1, 1, 1);
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Estrella3DText::Estrella3DText(GLdouble re, GLdouble ri, GLdouble np, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaEstrellaTextCor(re, ri, np, h);
}
//-------------------------------------------------------------------------

Estrella3DText::~Estrella3DText()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Estrella3DText::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_REPLACE);
		mMesh->render();

		dmat4 mI = dmat4(1);
		dmat4 rMat = rotate(mI, radians(180.0), dvec3(0.0, 1.0, 0.0));
		aMat = modelViewMat * mModelMat * rMat;
		upload(aMat);
		mMesh->render();

		glColor3d(1, 1, 1);
	}
}
//-------------------------------------------------------------------------

void Estrella3DText::update()	//la animacion de la estrella
{
	GLdouble radiusTranslation = 300, speedRotation = 4.0, speedTranslation = 4.0;

	dmat4 mI = dmat4(1);	//matriz unidad
	dmat4 rMat = rotate(mI, radians(speedRotation * frame), dvec3(0.0, 1.0, 0.9));
	dmat4 tMat = translate(mI, dvec3(100.0, 300.0, 100.0));
	setModelMat(tMat * rMat * mI);
	frame++;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloTextCor(w, h, rw, rh);
	this->setModelMat(rotate(this->modelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));
}
//-------------------------------------------------------------------------

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Suelo::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_REPLACE);
		mMesh->render();

		glColor3d(1, 1, 1);
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

CajaText::CajaText(GLdouble ld) : Abs_Entity()
{
	mMesh = Mesh::generaCajaTextCor(ld);
	suelo_ = Mesh::generaRectanguloTextCor(ld, ld, 1, 1);
}
//-------------------------------------------------------------------------

CajaText::~CajaText()
{
	delete mMesh; mMesh = nullptr;
	delete suelo_; suelo_ = nullptr;
};
//-------------------------------------------------------------------------

void CajaText::render(dmat4 const& modelViewMat) const
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
		mTextureInside->bind(GL_REPLACE);
		mMesh->render();

		dmat4 mI = dmat4(1);
		dmat4 rMat = rotate(mI, radians(90.0), dvec3(1.0, 0.0, 0.0));
		dmat4 tMat = translate(mI, dvec3(100.0, 100.0, -0.1));
		aMat = modelViewMat * mModelMat * rMat * tMat;
		upload(aMat);
		suelo_->render();

		glCullFace(GL_FRONT / GL_BACK);
		glDisable(GL_CULL_FACE);
		glColor3d(1, 1, 1);
	}
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Foto::Foto(GLdouble w, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloTextCor(w, h, 1, 1);
}
//-------------------------------------------------------------------------

Foto::~Foto()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Foto::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_REPLACE);
		mMesh->render();

		glColor3d(1, 1, 1);
	}
}

void Foto::update() {
	mTexture->loadColorBuffer();
}


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Cristalera::Cristalera(GLdouble ld) : Abs_Entity()
{
	mMesh = Mesh::generaCajaTextCor(ld);
}
//-------------------------------------------------------------------------

Cristalera::~Cristalera()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Cristalera::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_REPLACE);
		glColor4dv(value_ptr(mColor));
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mMesh->render();

		glColor3d(1, 1, 1);
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

QuadraticEntity::QuadraticEntity()
{
	q = gluNewQuadric();
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Sphere::Sphere(GLdouble r) { radius = r; }

void Sphere::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat; 
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(mColor.r, mColor.g, mColor.b);
	gluQuadricDrawStyle(q, GLU_FILL);

	gluSphere(q, radius, 50, 50);

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Cylinder::Cylinder(GLdouble bR, GLdouble tR, GLdouble h) { baseR = bR; topR = tR; height = h; }

void Cylinder::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(mColor.r, mColor.g, mColor.b);
	gluQuadricDrawStyle(q, GLU_FILL);

	gluCylinder(q, baseR, topR, height, 50, 50);

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Disk::Disk(GLdouble iR, GLdouble oR) { innerR = iR; outerR = oR; }

void Disk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(mColor.r, mColor.g, mColor.b);
	gluQuadricDrawStyle(q, GLU_FILL);

	gluDisk(q, innerR, outerR, 50, 50);

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

PartialDisk::PartialDisk(GLdouble iR, GLdouble oR, GLdouble stA, GLdouble swA) { innerR = iR; outerR = oR; startAngle = stA; sweepAngle = swA; }

void PartialDisk::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(mColor.r, mColor.g, mColor.b);
	gluQuadricDrawStyle(q, GLU_FILL);

	gluPartialDisk(q, innerR, outerR,startAngle, sweepAngle, 50, 50);

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


AnilloCuadrado::AnilloCuadrado()
{
	mMesh = Mesh::generaAnilloCuadrado();
}

AnilloCuadrado::~AnilloCuadrado()
{
	delete mMesh;
	mMesh = nullptr;
}

void AnilloCuadrado::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		mMesh->render();
		glDisable(GL_COLOR_MATERIAL);
	}
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EntityWithIndexMesh::EntityWithIndexMesh()
{
	mMesh = IndexMesh::generaIndexCuboConTapas(100);
}

EntityWithIndexMesh::~EntityWithIndexMesh()
{
	delete mMesh; mMesh = nullptr;
}

void EntityWithIndexMesh::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glEnable(GL_COLOR_MATERIAL);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mMesh->render();

		glDisable(GL_COLOR_MATERIAL);
	}
}
