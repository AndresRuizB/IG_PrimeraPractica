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
		glEnable(GL_COLOR_MATERIAL);
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);

		glDisable(GL_COLOR_MATERIAL);
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

QuadricEntity::QuadricEntity()
{
	q = gluNewQuadric();
}

Sphere::Sphere(GLdouble rr) { r = rr; }

void Sphere::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	if (color != glm::fvec3(-1, -1, -1)) {
		// Aquí se puede fijar el color de la esfera así:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(color.r, color.g, color.b);
		// Aquí se puede fijar el modo de dibujar la esfera:
		gluQuadricDrawStyle(q, GLU_FILL);
	}
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

Cylinder::Cylinder(GLdouble baseR, GLdouble topR, GLdouble height) {
	bR = baseR;
	tR = topR;
	h = height;
}

void Cylinder::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	if (color != glm::fvec3(-1, -1, -1)) {
		// Aquí se puede fijar el color de la esfera así:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(color.r, color.g, color.b);
		// Aquí se puede fijar el modo de dibujar la esfera:
		gluQuadricDrawStyle(q, GLU_FILL);
	}
	gluCylinder(q, bR, tR, h, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

Disk::Disk(GLdouble innerR, GLdouble outerR)
{
	iR = innerR;
	oR = outerR;
}

void Disk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	if (color != glm::fvec3(-1, -1, -1)) {
		// Aquí se puede fijar el color de la esfera así:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(color.r, color.g, color.b);
		// Aquí se puede fijar el modo de dibujar la esfera:
		gluQuadricDrawStyle(q, GLU_FILL);
	}
	gluDisk(q, iR, oR, 50, 40);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

PartialDisk::PartialDisk(GLdouble innerR, GLdouble outerR, GLdouble startAngle, GLdouble sweepAngle)
{
	iR = innerR;
	oR = outerR;
	stAngle = startAngle;
	swAngle = sweepAngle;
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	if (color != glm::fvec3(-1, -1, -1)) {
		// Aquí se puede fijar el color de la esfera así:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(color.r, color.g, color.b);
		// Aquí se puede fijar el modo de dibujar la esfera:
		gluQuadricDrawStyle(q, GLU_FILL);
	}
	gluPartialDisk(q, iR, oR, 50, 50, stAngle, swAngle);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
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

}

EntityWithIndexMesh::~EntityWithIndexMesh()
{
	delete iMesh; iMesh = nullptr;
}

void EntityWithIndexMesh::render(glm::dmat4 const& modelViewMat) const
{
	if (iMesh != nullptr) {
		glEnable(GL_COLOR_MATERIAL);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glColor3f(mColor.r, mColor.g, mColor.b);
		// Aquí se puede fijar el modo de dibujar la esfera:

		iMesh->render();

		glDisable(GL_COLOR_MATERIAL);
		// Aquí se debe recuperar el color:
		glColor3f(1.0, 1.0, 1.0);
	}
}

Cubo::Cubo(GLdouble l)
{
	iMesh = IndexMesh::generaIndexCuboConTapas(l);
	iMesh->buildNormals();
}

Cubo::~Cubo()
{
}

void Cubo::render(glm::dmat4 const& modelViewMat) const
{
	EntityWithIndexMesh::render(modelViewMat);
}

CompoundEntity::CompoundEntity()
{
}

CompoundEntity::~CompoundEntity()
{
	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{

	glEnable(GL_COLOR_MATERIAL);
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);

	for (Abs_Entity* ob : gObjects) {
		ob->render(aMat);
	}

	glDisable(GL_COLOR_MATERIAL);
	
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}


Cono::Cono(GLdouble h, GLdouble r, GLuint n)
{
	// h=altura del cono, r=radio de la base
// n=número de muestras, m=número de puntos del perfil
	int m = 3;
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.5, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.5, h, 0.0);
	this->iMesh = MbR::generaIndexMeshByRevolution(m,n,perfil);

}

Esfera::Esfera(GLdouble r, GLdouble p, GLuint m)
{
// m=número de muestras, p=número de puntos del perfil
	dvec3* perfil = new dvec3[p+1];
	float anglePerSegment = 180/(p-1);
	float currentAngle = -90;
	for (int i = 0; i < p; i++) {
		perfil[i] = dvec3(cos(radians(currentAngle)) * r, sin(radians(currentAngle)) * r, 0.0);
		currentAngle += anglePerSegment;
	}
	perfil[int(p)] = glm::dvec3(0,-r,0);

	this->iMesh = MbR::generaIndexMeshByRevolution(p, m, perfil);
}
