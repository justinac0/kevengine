#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "BufferUtil.h"

class Mesh {
private:
    GLuint vaoID;
    GLuint vboID;
    GLuint nboID;
    GLuint iboID;

    uint32_t indexCount;

public:
    Mesh(void);
    Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<GLuint> indices);
    ~Mesh(void);

    void cleanup(void);

    void draw(void);

    GLuint getVaoID(void);
};

#endif // MESH_H
