//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <iostream>
#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	virtual void update();  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	void setTexture(Texture* const& aTex) { mTexture = aTex; };
	
	void changeColor(glm::dvec4 const& color) {mColor = color; };

protected:

	Mesh* mMesh = nullptr;   // the mesh
	Texture* mTexture = nullptr;
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;
	int frame = 0;

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Poligono : public Abs_Entity
{
public:
	explicit Poligono(GLuint numL,GLdouble rd);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Sierpinsky : public Abs_Entity
{
public:
	explicit Sierpinsky(GLuint numL, GLdouble rd);
	~Sierpinsky();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class TrianguloRGB : public Abs_Entity
{
public:
	explicit TrianguloRGB(GLdouble rd);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

//-------------------------------------------------------------------------
class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
//-------------------------------------------------------------------------
class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	glm::dmat4 const& modelMat2() const { return mModelMat2; };
	void setModelMat2(glm::dmat4 const& aMat) { mModelMat2 = aMat; };
	void setTexture2(Texture* const& aTex) { mTexture2 = aTex; };

	glm::dmat4 mModelMat2;
private:
	Mesh* mMesh2 = nullptr;
	Texture* mTexture2 = nullptr;
};
//-------------------------------------------------------------------------
class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};
//-------------------------------------------------------------------------
class Foto : public Abs_Entity
{
public:
	explicit Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
//-------------------------------------------------------------------------
class Cristalera : public Abs_Entity
{
public:
	explicit Cristalera(GLdouble ld);
	~Cristalera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------
class Planta : public Abs_Entity
{
public:
	explicit Planta(GLdouble ld);
	~Planta();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
#endif //_H_Entities_H_