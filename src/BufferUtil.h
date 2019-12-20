#ifndef BUFFER_UTIL_H
#define BUFFER_UTIL_H

#include <glad/glad.h>

namespace BufferUtil {
    void bindVaoID(GLuint vaoID);
    GLuint createVaoID(void);
    void destroyVaoID(GLuint* vaoID);

    GLuint createBufferID(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
    void destroyBufferID(GLuint* bufferID);

    void setAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    void enableVertexAtrribArray(GLuint index);
};

#endif // BUFFER_UTIL_H
