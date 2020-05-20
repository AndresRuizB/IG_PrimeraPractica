#include "MbR.h"
using namespace glm;

MbR::~MbR()
{
}

MbR* MbR::generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil)
{
	MbR* mesh = new MbR(mm, nn, perfil);
	// Definir la primitiva como GL_TRIANGLES
	mesh->mPrimitive = GL_TRIANGLES;
	// Definir el número de vértices como nn*mm
	mesh->mNumVertices = nn * mm;
	// Usar un vector auxiliar de vértices
	glm::dvec3* vertices = new glm::dvec3[mesh->mNumVertices];

	for (int i = 0; i < nn; i++) {
		// Generar la muestra i-ésima de vértices
		GLdouble theta = i * 360 / nn;
		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));
		// R_y(theta) es la matriz de rotación alrededor del eje Y
		for (int j = 0; j < mm; j++) {
			int indice = i * mm + j;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			vertices[indice] = glm::dvec3(x, perfil[j].y, z);
		}
	}

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vVertices.emplace_back(vertices[i]);
	}

	int indiceMayor = 0;
	mesh->nNumIndices = nn * (mm-1) * 6;
	mesh->vIndices = new GLuint[mesh->nNumIndices];
	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nn; i++)
		// El contador j recorre los vértices del perfil,
		// de abajo arriba. Las caras cuadrangulares resultan
		// al unir la muestra i-ésima con la (i+1)%nn-ésima
		for (int j = 0; j < mm - 1; j++) {
		// El contador indice sirve para llevar cuenta
		// de los índices generados hasta ahora. Se recorre
		// la cara desde la esquina inferior izquierda
			int indice = i * mm + j;
		// Los cuatro índices son entonces:
		//indice, (indice + mm) % (nn * mm), (indice + mm + 1) % (nn * mm), indice + 1

			mesh->vIndices[indiceMayor] = indice; 
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;

			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice + 1;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice;
			indiceMayor++;

		}

	mesh->buildNormals();
	return mesh;
}