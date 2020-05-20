#include "IndexMesh.h"

glm::dvec3 IndexMesh::getNormal(const std::vector<glm::dvec3>& vFace)
{
	return glm::normalize(glm::cross((vFace[2] - vFace[1]), (vFace[0] - vFace[1])));
}

IndexMesh* IndexMesh::generaIndexCuboConTapas(GLdouble l)
{
	IndexMesh* iMesh = new IndexMesh();

	iMesh->mNumVertices = 10;

	iMesh->vVertices.reserve(iMesh->mNumVertices);
	iMesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	iMesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	iMesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	iMesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	iMesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	iMesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	iMesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	iMesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);

	iMesh->nNumIndices = 36;
	iMesh->vIndices = std::vector<GLuint>{
	0,1,2,2,1,3,
	2,3,4,4,3,5,
	4,5,6,6,5,7,
	6,7,0,0,7,1,
	4,6,2,2,6,0,
	1,7,3, 3,7,5
	};

	iMesh->vColors.reserve(iMesh->mNumVertices);
	glm::dvec4 green = { 0.0, 1.0, 0.2, 1.0 };

	for (int i = 0; i < iMesh->mNumVertices; i++) {
		iMesh->vColors.emplace_back(green);
	}

	return iMesh;
}

void IndexMesh::render() const
{
	if (vVertices.size() > 0) {  // transfer data
  // transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
		}
		if (vTextCoords.size() > 0) { // transfer colors
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTextCoords.data());  // components number (rgba=4), type of each component, stride, pointer  
		}

		if (vIndices.data() != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndices.data());
		}

		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}

		draw();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

void IndexMesh::draw() const
{
	glDrawElements(mPrimitive, nNumIndices, GL_UNSIGNED_INT, vIndices.data());
}


void IndexMesh::buildNormals()
{
	vNormals.reserve(mNumVertices);
	for (int i = 0; i < mNumVertices; i++) vNormals.emplace_back(0, 0, 0);

	for (int i = 0; i < nNumIndices; i += 3) {

		std::vector<glm::dvec3> faceTemp;
		faceTemp.push_back(vVertices[vIndices[i]]);
		faceTemp.push_back(vVertices[vIndices[i + 1]]);
		faceTemp.push_back(vVertices[vIndices[i + 2]]);

		glm::dvec3 normal = getNormal(faceTemp);

		for (int z = 0; z < 3; z++) {
			vNormals[vIndices[(i + z) % nNumIndices]] += normal;
		}
	}

	for (int i = 0; i < mNumVertices; i++) {
		vNormals[i] = glm::normalize(vNormals[i]);
	}
}

//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------


MbR* MbR::generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil)
{

	MbR* mesh = new MbR(nn, perfil, mm);

	mesh->mNumVertices = nn * mm;

	glm::dvec3* vertices = new glm::dvec3[mesh->mNumVertices];

	// Definir la primitiva como GL_TRIANGLES
	// Definir el número de vértices como nn*mm
	// Usar un vector auxiliar de vértices
	// dvec3* vertices = new dvec3[mesh->mNumVertices];
	for (int i = 0; i < nn; i++) {
		// Generar la muestra i-ésima de vértices
		GLdouble theta = i * 360 / nn;
		GLdouble c = cos(glm::radians(theta));
		GLdouble s = sin(glm::radians(theta));
		// R_y(theta) es la matriz de rotación alrededor del eje Y
		for (int j = 0; j < mm; j++) {
			int indice = i * mm + j;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			vertices[indice] = glm::dvec3(x, perfil[j].y, z);
		}
	}

	for (int i = 0; i < mesh->mNumVertices; i++) {

		mesh->vVertices.push_back(vertices[i]);
	}


	int indiceMayor = 0;

	mesh->nNumIndices = nn * (mm - 1) * 6;
	mesh->vIndices = std::vector<GLuint>(mesh->nNumIndices);

	for (int i = 0; i < nn; i++) {
		// El contador j recorre los vértices del perfil,
		// de abajo arriba. Las caras cuadrangulares resultan
		// al unir la muestra i-ésima con la (i+1)%nn-ésima
		for (int j = 0; j < mm - 1; j++) {
			// El contador indice sirve para llevar cuenta
			// de los índices generados hasta ahora. Se recorre
			// la cara desde la esquina inferior izquierda
			int indice = i * mm + j;

			mesh->vIndices.push_back(indice);
			indiceMayor++;
			mesh->vIndices.push_back((indice + mm) % (nn * mm));
			indiceMayor++;
			mesh->vIndices.push_back((indice + mm + 1) % (nn * mm));
			indiceMayor++;

			mesh->vIndices.push_back((indice + mm + 1) % (nn * mm));
			indiceMayor++;
			mesh->vIndices.push_back(indice + 1);
			indiceMayor++;
			mesh->vIndices.push_back(indice);
			indiceMayor++;
		}
	}

	mesh->nNumIndices = mesh->vIndices.size();
	mesh->buildNormals();

	for (int i = 0; i < mesh->mNumVertices; i++) {

		mesh->vColors.push_back({0.0,0.0,1.0,1.0});
	}

	return mesh;

}

//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------