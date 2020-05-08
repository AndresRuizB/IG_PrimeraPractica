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
	iMesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	iMesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	iMesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	iMesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	iMesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	iMesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	iMesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	iMesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);

	iMesh->nNumIndices = 36;
	iMesh->vIndices = new GLuint[iMesh->nNumIndices]{
	0,1,2,2,1,3,
	2,3,4,4,3,5,
	4,5,6,6,5,7,
	6,7,0,0,7,1,
	4,6,2,2,6,0,
	1,7,3, 3,7,5
	};

	iMesh->vColors.reserve(iMesh->mNumVertices);
	glm::dvec4 red = {1.0, 0.0, 0.0, 1.0};

	for (int i = 0; i < iMesh->mNumVertices; i++) {
		iMesh->vColors.emplace_back(red);
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
	glDrawElements(mPrimitive, nNumIndices,
		GL_UNSIGNED_INT, vIndices);
}

void IndexMesh::buildNormals()
{
	vNormals.reserve(mNumVertices);
	for (int x = 0; x < mNumVertices; x++) vNormals.emplace_back(0, 0, 0);

	for (int i = 0; i < nNumIndices; i += 3) {
		std::vector<glm::dvec3> faceTemp;
		faceTemp.push_back(vVertices[vIndices[i]]);
		faceTemp.push_back(vVertices[vIndices[i + 1]]);
		faceTemp.push_back(vVertices[vIndices[i + 2]]);

		glm::dvec3 normal = getNormal(faceTemp);

		for (int z = 0; z < 3; z++) {
			vNormals[vIndices[i + z]] += normal;
		}
	}

	for (int y = 0; y < mNumVertices; y++) {
		vNormals[y] = glm::normalize(vNormals[y]);
	}
}
