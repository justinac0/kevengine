#ifndef MESH_HPP_
#define MESH_HPP_

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "BufferUtil.hpp"

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

#endif // MESH_HPP_
