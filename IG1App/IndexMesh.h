#pragma once
#include "Mesh.h"

class IndexMesh : public Mesh {

private:
    glm::dvec3 getNormal(const std::vector<glm::dvec3>& vFace);

protected:
    GLuint* vIndices = nullptr;
    GLuint nNumIndices = 0;

public:

    static IndexMesh* generaIndexCuboConTapas(GLdouble l);

    IndexMesh() { mPrimitive = GL_TRIANGLES; }
    ~IndexMesh() { delete[] vIndices; }
    virtual void render() const override;
    virtual void draw() const;

    void buildNormals();
};

