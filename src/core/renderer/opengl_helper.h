#ifndef OPENGL_HELPER_H
#define OPENGL_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../../deps/glad/glad.h"

#include "../utility/util.h"
#include "../utility/math.h"

/* BUFFERS */
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

/* SHADERS */
// compile individual shader source.
GLuint ogl_shader_compile(const char* fileLocation, const int shaderType);
// loads in default built-in shaders.
GLuint ogl_shader_load_default(void);
// load in vertex and fragment shaders and return shader program ID.
GLuint ogl_shader_load(const char* vsFileLocation, const char* fsFileLocation);
// use given shader.
void ogl_shader_use(GLuint programID);

/* SHADER UNIFORMS */
// send vec3 to shader
void ogl_shader_uniform_vec3(GLfloat programID, const char* name, vec3_t* vector);
// send mat4 to shader
void ogl_shader_uniform_mat4(GLfloat programID, const char* name, mat4_t* matrix);

/* DRAWING */
// draw primitives
void ogl_draw(const int drawType, GLuint vaoID, uint32_t iCount);

#endif // OPENGL_HELPER_H
