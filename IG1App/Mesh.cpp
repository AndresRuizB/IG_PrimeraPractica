#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const
{
	glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const
{
	if (vVertices.size() > 0) {  // transfer data
	  // transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
		}
		if (vTexCoords.size() > 0) { // transfer colors
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());  // components number (rgba=4), type of each component, stride, pointer  
		}

		draw();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}
//-------------------------------------------------------------------------

Mesh* Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = numL;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble tempAng = 90.0;
	GLdouble increment = 360.0 / numL;

	for (int i = 0; i < numL; i++) {
		mesh->vVertices.emplace_back(rd * cos(radians(tempAng)), rd * sin(radians(tempAng)), 0.0);
		tempAng += increment;
	}

	return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaSierpinsky(GLdouble rd, GLuint numP)
{
	Mesh* tri = generaPoligono(3, rd);
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_POINTS;

	mesh->mNumVertices = numP;
	mesh->vVertices.reserve(mesh->mNumVertices);

	glm::dvec3 vTemp = tri->vVertices[rand() % 3];

	for (int i = 0; i < numP; i++) {
		mesh->vVertices.emplace_back(vTemp);
		GLuint v = rand() % 3;
		vTemp = dvec3((vTemp.x + tri->vVertices[v].x) / 2.0, (vTemp.y + tri->vVertices[v].y) / 2.0, (vTemp.z + tri->vVertices[v].z) / 2.0);
	}

	delete tri;
	tri = nullptr;

	return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaTrianguloRGB(GLdouble rd)
{
	Mesh* mesh = generaPoligono(3, rd);

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	glPolygonMode(GL_BACK, GL_POINT);

	return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4;

	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vVertices.emplace_back(-w / 2, h / 2, 0);
	mesh->vVertices.emplace_back(-w / 2, -h / 2, 0);
	mesh->vVertices.emplace_back(w / 2, h / 2, 0);
	mesh->vVertices.emplace_back(w / 2, -h / 2, 0);


	return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
	Mesh* mesh = generaRectangulo(w, h);

	mesh->vColors.reserve(mesh->mNumVertices);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 0.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 0.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 0.0);
	mesh->vColors.emplace_back(0.0, 0.0, 0.0, 0.0);

	return mesh;
}

Mesh* Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	mesh->mNumVertices = 2*np+2;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble tempAng = 90.0;
	GLdouble increment = 360.0 / (np*2);

	mesh->vVertices.emplace_back(0.0,0.0,0.0);

	for (int i = 0; i < mesh->mNumVertices-1; i++) {
		mesh->vVertices.emplace_back(re/(1+(i%2)) * cos(radians(tempAng)), re/ (1 + (i % 2)) * sin(radians(tempAng)), h);
		tempAng += increment;
	}

	return mesh;
}

Mesh* Mesh::generaContCubo(GLdouble ld)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;

	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vVertices.emplace_back(-ld / 2, ld / 2, ld / 2);
	mesh->vVertices.emplace_back(-ld / 2, -ld / 2, ld / 2);
	mesh->vVertices.emplace_back(ld / 2, ld / 2, ld / 2);
	mesh->vVertices.emplace_back(ld / 2, -ld / 2, ld / 2);
	mesh->vVertices.emplace_back(ld / 2, ld / 2, -ld / 2);
	mesh->vVertices.emplace_back(ld / 2, -ld / 2, -ld / 2);
	mesh->vVertices.emplace_back(-ld / 2, ld / 2, -ld / 2);
	mesh->vVertices.emplace_back(-ld / 2, -ld / 2, -ld / 2);
	mesh->vVertices.emplace_back(-ld / 2, ld / 2, ld / 2);
	mesh->vVertices.emplace_back(-ld / 2, -ld / 2, ld / 2);


	return mesh;
}

Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLdouble np, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	mesh->mNumVertices = 2 * np + 2;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble tempAng = 90.0;
	GLdouble increment = 360.0 / (np * 2);

	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);

	for (int i = 0; i < mesh->mNumVertices - 1; i++) {
		mesh->vVertices.emplace_back(re / (1 + (i % 2)) * cos(radians(tempAng)), re / (1 + (i % 2)) * sin(radians(tempAng)), h);
		tempAng -= increment;
	}

	mesh->vTexCoords.reserve(mesh->mNumVertices);
	mesh->vTexCoords.emplace_back(0.5, 0.5);

	double x = 0, y = 0;
	for (int i = 0; i < mesh->mNumVertices - 1; i++) {
		mesh->vTexCoords.emplace_back(x, y);
		
		if (x == 1 && y < 1) y += 0.5;
		else if (x < 1 && y == 0) x += 0.5;
		else if (x > 0 && y == 1) x -= 0.5;
		else if (x == 0 && y > 0) y -= 0.5;

	}
	return mesh;
}

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* mesh = generaRectangulo(w, h);

	GLdouble wR = 1;
	GLdouble hR = 1;

	//Descomentar para tilear la textura
	//if(w / h>1)
	// wR = w / h;
	//if(h / w>1)
	//hR = h / w;


	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(dvec2(0,rh*hR));
	mesh->vTexCoords.emplace_back(dvec2(0, 0));
	mesh->vTexCoords.emplace_back(dvec2(rw*wR, rh*hR));
	mesh->vTexCoords.emplace_back(dvec2(rw*wR, 0));


	return mesh;
}

Mesh* Mesh::generaCajaTexCor(GLdouble nl)
{
	Mesh* mesh = generaContCubo(nl);

	mesh->vTexCoords.reserve(mesh->mNumVertices);
	for (int i = 0; i < 4; i++) {
		mesh->vTexCoords.emplace_back(0.0, 1.0);
		mesh->vTexCoords.emplace_back(0.0, 0.0);
		mesh->vTexCoords.emplace_back(1.0, 1.0);
		mesh->vTexCoords.emplace_back(1.0, 0.0);
	}

	return mesh;
}
