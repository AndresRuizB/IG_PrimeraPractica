//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <iostream>
#include "Mesh.h"

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
	
	void changeColor(glm::dvec4 const& color) {mColor = color; };

protected:

	Mesh* mMesh = nullptr;   // the mesh
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
	explicit Estrella3D(GLdouble re, GLdouble ri, GLdouble np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_