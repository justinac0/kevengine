#ifndef OGL_H
#define OGL_H

#include "../deps/glad/glad.h"
#include <GLFW/glfw3.h>

void ogl_setup(void);
void ogl_clear(float r, float g, float b, float a);

GLuint ogl_gen_vertex_buffer_object();
GLfloat ogl_gen_buffer_object_float();
GLuint ogl_gen_buffer_object_uint();

#endif // OGL_H
