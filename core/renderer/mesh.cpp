#include "mesh.hpp"

// TODO(justin) : move this out of the mesh source
namespace opengl_buffer {

    GLuint VertexArrayCreate() {
        GLuint vertexArrayID;
        glGenVertexArrays(1, &vertexArrayID);

        return vertexArrayID;
    }

    void VertexArrayBind(GLuint id) {
        glBindVertexArray(id);
    }

    GLuint FloatBufferCreate(GLenum type, GLenum usage, float* data, uint32_t count) {
        GLuint bufferID;
        glGenBuffers(1, &bufferID);
        glBindBuffer(type, bufferID);
        glBufferData(type, sizeof(float) * count, data, usage);

        return bufferID;
    }

    GLuint ShortBufferCreate(GLenum type, GLenum usage, short* data, uint32_t count) {
        GLuint bufferID;
        glGenBuffers(1, &bufferID);
        glBindBuffer(type, bufferID);
        glBufferData(type, sizeof(short) * count, data, usage);

        return bufferID;
    }

    GLuint IntBufferCreate(GLenum type, GLenum usage, int* data, uint32_t count) {
        GLuint bufferID;
        glGenBuffers(1, &bufferID);
        glBindBuffer(type, bufferID);
        glBufferData(type, sizeof(int) * count, data, usage);

        return bufferID;
    }

}

using namespace kevin::renderer;

Mesh::Mesh() {
    // default
}

Mesh::Mesh(std::vector<float> vertices, std::vector<float> colours, std::vector<int> indices) {
    this->m_vertCount = vertices.size();
    this->m_idxCount = indices.size();
    this->m_vaoID = opengl_buffer::VertexArrayCreate();

    opengl_buffer::VertexArrayBind(this->m_vaoID);

    opengl_buffer::FloatBufferCreate(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices.data(), this->m_vertCount * sizeof(float));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    opengl_buffer::FloatBufferCreate(GL_ARRAY_BUFFER, GL_STATIC_DRAW, colours.data(), colours.size() * sizeof(float));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    opengl_buffer::IntBufferCreate(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices.data(), this->m_idxCount);

    opengl_buffer::VertexArrayBind(0);
}

Mesh::~Mesh() { }

void Mesh::DrawElements() {
    glBindVertexArray(this->m_vaoID);
    glDrawElements(GL_TRIANGLES, this->m_idxCount, GL_UNSIGNED_INT, nullptr);
}

void Mesh::DrawArrays() {
    glBindVertexArray(this->m_vaoID);
    glDrawArrays(GL_TRIANGLES, 0, this->m_vertCount);
}

GLuint Mesh::GetVaoID() {
    return this->m_vaoID;
}
