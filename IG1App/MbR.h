#pragma once
#include "IndexMesh.h"

class MbR : public IndexMesh
{
public:
	/*numero de muestras (rotaciones)*/
	int n;
	/*array de v�rtices que define el perfil*/
	glm::dvec3* perfil;
	/*n�mero de puntos del perfil*/
	int m;

	MbR(int n, int m, glm::dvec3* perfil) : n(n), m(m), perfil(perfil) {};
	~MbR();

	static MbR* generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil);
};

