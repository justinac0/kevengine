#include "BufferUtil.hpp"

namespace BufferUtil {

    void bindVaoID(GLuint vaoID) {
        glBindVertexArray(vaoID);
    }

    GLuint createVaoID(void) {
        GLuint vaoID;

        glGenVertexArrays(1, &vaoID);
        bindVaoID(vaoID);

        return vaoID;
    }

    void destroyVaoID(GLuint* vaoID) {
        glDeleteVertexArrays(1, vaoID);
        bindVaoID(0);
    }

    GLuint createBufferID(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
        GLuint bufferID;

        glGenBuffers(1, &bufferID);
        glBindBuffer(target, bufferID);
        glBufferData(target, size, data, usage);

        return bufferID;
    }

    void destroyBufferID(GLuint* bufferID) {
        glDeleteBuffers(1, bufferID);
    }


    GLuint createTextureID(GLenum target) {
        GLuint textureID;

        glGenTextures(1, &textureID);
        glBindTexture(target, textureID);

        return textureID;
    }
 
    void destroyTextureID(GLuint* textureID) {
        glDeleteTextures(1, textureID);
    }

    void setAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    }

    void enableVertexAtrribArray(GLuint index) {
        glEnableVertexAttribArray(index);
    }

};
