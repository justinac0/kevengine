#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../deps/glad/glad.h"
#include <GLFW/glfw3.h>

#include "util.h"

typedef struct {
    GLFWwindow* window;
} r_context_t;

// renderer specific functions.
void r_context_create(r_context_t* renderer, uint32_t width, uint32_t height, const char* title);
void r_context_destroy(r_context_t* renderer);
void r_context_update(GLFWwindow* pWindow);

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
    GLuint vboID;
    GLuint iCount;
} r_mesh_t;

r_mesh_t r_mesh_triangle_generate(void);
r_mesh_t r_mesh_obj(const char* fileLocation);

// model specific functions.
typedef struct {
    GLfloat* vertices;
    GLfloat* normals;
    GLuint* faces;
} r_model_t;

r_model_t r_model_create(const char* fileLocation);

// mesh batching specific functions.
typedef struct {
    GLuint  vaoID;
    GLuint* vboID;
    GLuint  iCount;
} r_batch_t;

void r_batch_create(r_batch_t* batch);

#endif // RENDERER_H
