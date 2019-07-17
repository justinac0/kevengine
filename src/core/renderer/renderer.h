#ifndef RENDERER_H
#define RENDERER_H

#include "ogl.h"
#include "window.h"

typedef struct renderer_t {
    const char* api; // default is OpenGL.
    GLFWwindow* window; // glfw specific window.
} renderer_t;

renderer_t renderer_create(unsigned int width, unsigned int height);
void renderer_destroy(renderer_t* renderer);

#endif // RENDERER_H
