#ifndef OPENGL_HELPER_H
#define OPENGL_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../../deps/glad/glad.h"

// create vaoID.
GLuint ogl_vertex_buffer_create(void);
// create char buffer.
GLuint ogl_buffer_create_c(uint32_t size, GLchar* data, GLenum target, GLenum usage);
// create short buffer.
GLuint ogl_buffer_create_s(uint32_t size, GLshort* data, GLenum target, GLenum usage);
// create int buffer.
GLuint ogl_buffer_create_i(uint32_t size, GLuint* data, GLenum target, GLenum usage);
// create float buffer.
GLuint ogl_buffer_create_f(uint32_t size, GLfloat* data, GLenum target, GLenum usage);
// delete buffer.
void ogl_buffer_delete(GLuint* bufferObject);

void ogl_draw(const int drawType, GLuint vaoID, uint32_t iCount);

#endif // OPENGL_HELPER_H
