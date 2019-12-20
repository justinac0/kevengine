#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> colors, std::vector<GLuint> indices) {
    this->vaoID = BufferUtil::createVaoID();

    this->vboID = BufferUtil::createBufferID(GL_ARRAY_BUFFER, vertices.capacity() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    BufferUtil::setAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    BufferUtil::enableVertexAtrribArray(0);

    this->cboID = BufferUtil::createBufferID(GL_ARRAY_BUFFER, colors.capacity() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
    BufferUtil::setAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);
    BufferUtil::enableVertexAtrribArray(1);

    this->iboID = BufferUtil::createBufferID(GL_ELEMENT_ARRAY_BUFFER, indices.capacity() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    this->indexCount = indices.capacity();

    BufferUtil::bindVaoID(0);
}

Mesh::~Mesh() {
    this->cleanup();
}

void Mesh::cleanup() {
    BufferUtil::destroyBufferID(&this->cboID);
    BufferUtil::destroyBufferID(&this->iboID);
    BufferUtil::destroyBufferID(&this->vboID);
    BufferUtil::destroyVaoID(&this->vaoID);
    BufferUtil::bindVaoID(0);
}

void Mesh::draw() {
    BufferUtil::bindVaoID(this->vaoID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    BufferUtil::bindVaoID(0);
}


GLuint Mesh::getVaoID() {
    return this->vaoID;
}