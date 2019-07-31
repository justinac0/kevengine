#ifndef OGL_H
#define OGL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../lib/cglm/include/cglm/cglm.h"

typedef struct mesh_t {
    GLuint          vaoID;
    unsigned int    iCount;
    mat4            modelMatrix;
} mesh_t;

void ogl_setup(void);
void ogl_clear(float r, float g, float b, float a);

GLuint ogl_vertex_buffer_generate(void);
GLuint ogl_buffer_generate_float(unsigned int dataSize, GLfloat* data, GLenum target, GLenum usage);
GLuint ogl_buffer_generate_uint(unsigned int dataSize, GLuint* data, GLenum target, GLenum usage);
void ogl_buffer_delete(GLuint* buffer);

mesh_t ogl_quad_generate(float size, vec3 color);
mesh_t ogl_triangle_generate(float size);
mesh_t ogl_cube_generate(float size);

GLuint shader_compile(const char* filePath, int type);
GLuint shader_load(const char *vertexFilePath, const char *fragmentFilePath);

#endif // OGL_H
