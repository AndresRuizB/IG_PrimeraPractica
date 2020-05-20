//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <iostream>
#include "Mesh.h"
#include "Texture.h"
#include "IndexMesh.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity() : mModelMat(1.0), mColor(0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	virtual void update();  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	void changeColor(glm::dvec4 const& color) { mColor = color; };

	void setTexture(Texture* tex) { mTexture = tex; };
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
	explicit Poligono(GLuint numL, GLdouble rd);
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

class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Estrella3DText : public Abs_Entity
{
public:
	explicit Estrella3DText(GLdouble re, GLdouble ri, GLdouble np, GLdouble h);
	~Estrella3DText();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

//-------------------------------------------------------------------------

class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class CajaText : public Abs_Entity
{
public:
	explicit CajaText(GLdouble ld);
	~CajaText();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void setTextureInside(Texture* tex) { mTextureInside = tex; };
private:
	Texture* mTextureInside = nullptr;
	Mesh* suelo_ = nullptr;
};

//-------------------------------------------------------------------------
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
//-------------------------------------------------------------------------

class Cristalera : public Abs_Entity
{
public:
	explicit Cristalera(GLdouble ld);
	~Cristalera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class QuadraticEntity : public Abs_Entity
{
public:
	explicit QuadraticEntity();
	virtual~QuadraticEntity() { gluDeleteQuadric(q); };
	void setQuadricObjColor(glm::fvec3 c) { mColor = c; };
protected:
	GLUquadricObj* q;
	glm::fvec3 mColor = glm::fvec3(1.0, 1.0, 1.0);
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Sphere : public QuadraticEntity
{
public:
	explicit Sphere(GLdouble radius);
	void render(glm::dmat4 const& modelViewMat) const ;
protected:
	GLdouble radius;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Cylinder : public QuadraticEntity
{
public:
	explicit Cylinder(GLdouble bR, GLdouble tR, GLdouble h);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble baseR, topR;
	GLdouble height;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Disk : public QuadraticEntity
{
public:
	explicit Disk(GLdouble iR, GLdouble oR);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerR, outerR;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class PartialDisk : public QuadraticEntity
{
public:
	explicit PartialDisk(GLdouble iR, GLdouble oR, GLdouble stA, GLdouble swA );
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerR, outerR;
	GLdouble startAngle, sweepAngle;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class AnilloCuadrado : public Abs_Entity
{
public:
	explicit AnilloCuadrado();
	~AnilloCuadrado();
	void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class EntityWithIndexMesh : public Abs_Entity
{
public:
	explicit EntityWithIndexMesh();
	virtual ~EntityWithIndexMesh();
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	IndexMesh* iMesh = nullptr;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Cubo : public EntityWithIndexMesh
{
public:
	explicit Cubo(int l);
	virtual ~Cubo(); 
	void render(glm::dmat4 const& modelViewMat) const;

};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class CompoundEntity : public Abs_Entity
{
public:
	explicit CompoundEntity();
	virtual ~CompoundEntity();
	void render(glm::dmat4 const& modelViewMat) const;
	void addEntity(Abs_Entity* ae);
private:
	std::vector<Abs_Entity*> gObjects;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Cone : public EntityWithIndexMesh
{
public:
	explicit Cone(GLdouble h, GLdouble r, GLuint n);
	virtual ~Cone();
	void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Esfera : public EntityWithIndexMesh
{
public:
	explicit Esfera(GLdouble r, GLuint p, GLuint m);
	virtual ~Esfera();
	void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
#endif //_H_Entities_H_