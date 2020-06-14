//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <iostream>
#include "Mesh.h"
#include "Texture.h"
#include "MbR.h"
#include "Material.h"
#include "Light.h"
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
class QuadricEntity : public Abs_Entity
{
public:
	explicit QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
	void setQuadricObjColor(glm::fvec3 c) { color = c; };
protected:
	GLUquadricObj* q;
	glm::fvec3 color = glm::fvec3(-1, -1, -1);
};
//-------------------------------------------------------------------------
class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble r); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};
//-------------------------------------------------------------------------
class Cylinder : public QuadricEntity {
public:
	Cylinder(GLdouble baseR, GLdouble topR, GLdouble height);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble bR;
	GLdouble tR;
	GLdouble h;
};
//-------------------------------------------------------------------------
class Disk : public QuadricEntity {
public:
	Disk(GLdouble innerR, GLdouble outerR);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble iR;
	GLdouble oR;
};
//-------------------------------------------------------------------------
class PartialDisk : public QuadricEntity {
public:
	PartialDisk(GLdouble innerR, GLdouble outerR, GLdouble startAngle, GLdouble sweepAngle);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble iR;
	GLdouble oR;
	GLdouble stAngle;
	GLdouble swAngle;
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
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	IndexMesh* iMesh = nullptr;
};

//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class CompoundEntity : public Abs_Entity 
{
public:
	std::vector<Abs_Entity*> gObjects;

	CompoundEntity();
	~CompoundEntity();

	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
	virtual void addEntity(Abs_Entity* ae);
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Cono : public EntityWithIndexMesh 
{
public:
	explicit Cono(GLdouble h, GLdouble r, GLuint n);
	virtual ~Cono() {};
};

//-------------------------------------------------------------------------

class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { };

	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
	IndexMesh* iMesh = nullptr;
};
//-------------------------------------------------------------------------

class Cubo : public EntityWithMaterial
{
public:
	explicit Cubo(GLdouble l);
	virtual ~Cubo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------

class Esfera : public EntityWithMaterial
{
public:
	explicit Esfera(GLdouble r, GLdouble p, GLuint m);
	virtual ~Esfera() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------
class Plane : public CompoundEntity
{
public:
	Plane();
	virtual ~Plane() {};
	virtual void update();  // abstract method
	virtual void render(glm::dmat4 const& modelViewMat) const;
	SpotLight* getLight() { return spotLight; };
	void setHelices(CompoundEntity* h) { helices = h; };
private:
	SpotLight* spotLight = nullptr;
	CompoundEntity* helices = nullptr;
	double currentAngle = 180;
	float orbitRadius = 15;
};
//-------------------------------------------------------------------------
class Grid : public EntityWithMaterial
{
public:
	explicit Grid(GLdouble l, GLdouble nDiv);
	virtual ~Grid() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------

class GridCube : public CompoundEntity
{
public:
	GridCube() {};
	virtual ~GridCube() {};


private:

};

#endif //_H_Entities_H_