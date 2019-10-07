#include "opengl_helper.h"

GLuint ogl_vertex_buffer_create(void) {
    GLuint vaoID;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    return vaoID;
}

GLuint ogl_buffer_create_c(uint32_t size, GLchar* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint ogl_buffer_create_s(uint32_t size, GLshort* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint ogl_buffer_create_i(uint32_t size, GLuint* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint ogl_buffer_create_f(uint32_t size, GLfloat* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

void ogl_buffer_delete(GLuint* bufferObject) {
    glDeleteBuffers(1, bufferObject);
}

void ogl_draw(const int drawType, GLuint vaoID, uint32_t iCount) {
    glBindVertexArray(vaoID);
    glDrawElements(drawType, iCount, GL_UNSIGNED_INT, NULL);
}
