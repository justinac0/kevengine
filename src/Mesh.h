#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "BufferUtil.h"

// #define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

class Mesh {
private:
    GLuint vaoID;
    GLuint vboID; // vertex buffer
    GLuint nboID; // normals buffer
    GLuint cboID; // color buffer

    uint32_t vertCount;

    GLuint iboID;

    uint32_t indexCount;

public:
    Mesh(std::vector<float> primitiveData, std::vector<glm::vec3> normals, std::vector<GLuint> indices);
    ~Mesh(void);

    void cleanup(void);

    void draw(void);

    GLuint getVaoID(void);
};

#endif // MESH_H
