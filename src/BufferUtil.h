#ifndef BUFFER_UTIL_H
#define BUFFER_UTIL_H

#include <iostream>

#include <glad/glad.h>

namespace BufferUtil {
    // vao
    void bindVaoID(GLuint vaoID);
    GLuint createVaoID(void);
    void destroyVaoID(GLuint* vaoID);

    // buffers
    GLuint createBufferID(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
    void destroyBufferID(GLuint* bufferID);

    // textures
    GLuint createTextureID(GLenum target);
    void destroyTextureID(GLuint* textureID);

    // attribPointers
    void setAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    void enableVertexAtrribArray(GLuint index);
};

#endif // BUFFER_UTIL_H
