#ifndef MESH_H
#define MESH_H

#include <vector>
#include "BufferUtil.h"

class Mesh {
private:
    GLuint vaoID;
    GLuint vboID;
    GLuint iboID;
    GLuint cboID;

    uint32_t indexCount;

public:
    Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> colors, std::vector<GLuint> indices);
    ~Mesh();

    void cleanup();
    void draw();

    GLuint getVaoID();
};

#endif // MESH_H
