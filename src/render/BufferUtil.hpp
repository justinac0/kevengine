#ifndef BUFFER_UTIL_HPP_
#define BUFFER_UTIL_HPP_

#include <glad/glad.h>

namespace BufferUtil {
    void bindVaoID(GLuint vaoID);
    GLuint createVaoID(void);
    void destroyVaoID(GLuint* vaoID);

    GLuint createBufferID(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
    void destroyBufferID(GLuint* bufferID);

    GLuint createTextureID(GLenum target);
    void destroyTextureID(GLuint* textureID);

    void setAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    void enableVertexAtrribArray(GLuint index);
};

#endif // BUFFER_UTIL_HPP_
