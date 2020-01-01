#include "Mesh.h"

Mesh::Mesh(std::vector<float> primitiveData, std::vector<glm::vec3> normals, std::vector<GLuint> indices) { 
    this->vaoID = BufferUtil::createVaoID();

    this->vboID = BufferUtil::createBufferID(GL_ARRAY_BUFFER, primitiveData.capacity() * sizeof(float), primitiveData.data(), GL_STATIC_DRAW);
    BufferUtil::setAttribPointer(0, 3, GL_FLOAT, 0, 6 * sizeof(float), (GLvoid*)0);
    BufferUtil::enableVertexAtrribArray(0);

    BufferUtil::setAttribPointer(1, 3, GL_FLOAT, 0, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    BufferUtil::enableVertexAtrribArray(1);

    this->nboID = BufferUtil::createBufferID(GL_ARRAY_BUFFER, normals.capacity() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    BufferUtil::setAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);
    BufferUtil::enableVertexAtrribArray(2);

    this->iboID = BufferUtil::createBufferID(GL_ELEMENT_ARRAY_BUFFER, indices.capacity() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    this->vertCount = primitiveData.capacity() / 2;

    BufferUtil::bindVaoID(0);
}

Mesh::~Mesh(void) {
    this->cleanup();
}

void Mesh::cleanup(void) {
    BufferUtil::destroyBufferID(&this->iboID);
    BufferUtil::destroyBufferID(&this->cboID);
    BufferUtil::destroyBufferID(&this->nboID);
    // BufferUtil::destroyBufferID(&this->tboID);
    BufferUtil::destroyBufferID(&this->vboID);
    BufferUtil::destroyVaoID(&this->vaoID);
    BufferUtil::bindVaoID(0);  
}

void Mesh::draw(void) {
    BufferUtil::bindVaoID(this->vaoID);
    // glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, this->vertCount);
    BufferUtil::bindVaoID(0);
}

GLuint Mesh::getVaoID(void) {
    return this->vaoID;
}