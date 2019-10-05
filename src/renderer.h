#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "../deps/glad/glad.h"
#include <GLFW/glfw3.h>

#include "util.h"
#include "math.h"
#include "linmath.h"

// opengl abstracted util functions.
GLuint r_vertex_buffer_create(void);
GLuint r_buffer_create_c(uint32_t size, GLchar* data, GLenum target, GLenum usage);
GLuint r_buffer_create_s(uint32_t size, GLshort* data, GLenum target, GLenum usage);
GLuint r_buffer_create_i(uint32_t size, GLuint* data, GLenum target, GLenum usage);
GLuint r_buffer_create_f(uint32_t size, GLfloat* data, GLenum target, GLenum usage);
void r_buffer_object_delete(GLuint* bufferObject);

// opengl shader specific functions.
GLuint r_shader_compile(const char* fileLocation, const int shaderType);
GLuint r_shader_load(const char* vertexFileLocation, const char* fragmentFileLocation);
void r_shader_use(GLuint shaderProgramID);

// mesh specific functions.
typedef struct {
    GLuint vaoID;
    GLuint iCount;
    mat4_t modelMatrix;
} r_mesh_t;

r_mesh_t r_mesh_obj(const char* fileLocation);
void r_mesh_draw(r_mesh_t* mesh);

#endif // RENDERER_H
