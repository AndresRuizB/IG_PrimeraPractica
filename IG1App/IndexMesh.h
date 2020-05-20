#pragma once
#include "Mesh.h"

class IndexMesh : public Mesh {

private:
    glm::dvec3 getNormal(const std::vector<glm::dvec3>& vFace);

protected:
    std::vector<GLuint> vIndices ;
    GLuint nNumIndices = 0;

public:

    static IndexMesh* generaIndexCuboConTapas(GLdouble l);

    IndexMesh() { mPrimitive = GL_TRIANGLES; }
    ~IndexMesh() { }
    virtual void render() const override;
    virtual void draw() const;

    void buildNormals();
};

//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------

class MbR : public IndexMesh {

protected:
    int n_;  //numero muestras
    glm::dvec3* perfil_;
    int m_;  //puntos del perfil

public:

    MbR(int n, glm::dvec3* perfil, int m) :n_(n), perfil_(perfil), m_(m) {}
    ~MbR() { }

    static MbR* generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil);
};

//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
