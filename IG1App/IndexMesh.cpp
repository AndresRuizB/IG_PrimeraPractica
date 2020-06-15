#include "IndexMesh.h"

glm::dvec3 IndexMesh::getNormal(const std::vector<glm::dvec3>& vFace)
{
	return glm::cross((vFace[2] - vFace[1]), (vFace[0] - vFace[1]));
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
	iMesh->vIndices = new GLuint[iMesh->nNumIndices]{
	0,1,2,2,1,3,
	2,3,4,4,3,5,
	4,5,6,6,5,7,
	6,7,0,0,7,1,
	4,6,2,2,6,0,
	1,7,3, 3,7,5
	};

	//iMesh->vColors.reserve(iMesh->mNumVertices);
	//glm::dvec4 red = {1.0, 0.0, 0.0, 1.0};

	//for (int i = 0; i < iMesh->mNumVertices; i++) {
	//	iMesh->vColors.emplace_back(red);
	//}

	return iMesh;
}

IndexMesh* IndexMesh::generateGrid(GLdouble lado, GLuint nDiv)
{
	IndexMesh* iMesh = new IndexMesh();
	// h=altura del cono, r=radio de la base
// n=n�mero de muestras, m=n�mero de puntos del perfil
	int m = 3;
	glm::dvec3* perfil = new glm::dvec3[nDiv + 1];
	float startDist = -lado / 2;
	float squareLength = lado / nDiv;
	for (int i = 0; i < nDiv + 1; i++) {
		perfil[i] = glm::dvec3(startDist + squareLength * i, 0.0, 0.0);
	}
	int vertN = (nDiv + 1) * (nDiv + 1);
	iMesh->mNumVertices = vertN;

	glm::dvec3* vertices = new glm::dvec3[/*iMesh->mNumVertices*/vertN];
	int indice = 0;
	for (int i = 0; i < (nDiv + 1); i++) {
		for (int j = 0; j < (nDiv + 1); j++) {
			vertices[indice] = glm::dvec3(perfil[j].x, perfil[j].y, startDist + squareLength * i);
			indice++;
		}
	}

	for (int i = 0; i < iMesh->mNumVertices; i++) {
		iMesh->vVertices.emplace_back(vertices[i]);
	}
	delete[] perfil;
	delete[] vertices;

	int nn = (nDiv + 1);
	int mm = nn;
	int indiceMayor = 0;
	iMesh->nNumIndices = (nn - 1) * (mm - 1) * 6;
	iMesh->vIndices = new GLuint[iMesh->nNumIndices];
	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nn - 1; i++)
		// El contador j recorre los v�rtices del perfil,
		// de abajo arriba. Las caras cuadrangulares resultan
		// al unir la muestra i-�sima con la (i+1)%nn-�sima
		for (int j = 0; j < mm - 1; j++) {
			// El contador indice sirve para llevar cuenta
			// de los �ndices generados hasta ahora. Se recorre
			// la cara desde la esquina inferior izquierda
			int indice = i * mm + j;
			// Los cuatro �ndices son entonces:
			//indice, (indice + mm) % (nn * mm), (indice + mm + 1) % (nn * mm), indice + 1

			iMesh->vIndices[indiceMayor] = indice;
			indiceMayor++;
			iMesh->vIndices[indiceMayor] = (indice + mm) % (nn * mm);
			indiceMayor++;
			iMesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;

			iMesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;
			iMesh->vIndices[indiceMayor] = indice + 1;
			indiceMayor++;
			iMesh->vIndices[indiceMayor] = indice;
			indiceMayor++;

		}
	iMesh->buildNormals();

	return iMesh;
}

IndexMesh* IndexMesh::generateGridTex(GLdouble lado, GLuint nDiv)
{
	IndexMesh* im = generateGrid(lado, nDiv);

	im->vTextCoords.reserve((nDiv + 1)* (nDiv + 1));

	for (int i = 0; i < (nDiv + 1); i++) {
		for (int j = 0; j < (nDiv + 1); j++) {
			im->vTextCoords.emplace_back((float)j/(nDiv), (float)i / (nDiv));
		}
	}

	return im;
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

		if (vIndices != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
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
	glDrawElements(mPrimitive, nNumIndices, GL_UNSIGNED_INT, vIndices);
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
			vNormals[vIndices[(i + z)%nNumIndices]] += normal;
		}
	}

	for (int i = 0; i < mNumVertices; i++) {
		vNormals[i] = glm::normalize(vNormals[i]);
	}
}
