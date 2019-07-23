#ifndef RENDERER_H
#define RENDERER_H

#include "ogl.h"
#include "window.h"
#include "entity.h"
#include "camera.h"

typedef struct renderer_t {
    GLFWwindow* window;
} renderer_t;

renderer_t renderer_create(unsigned int width, unsigned int height);
void renderer_destroy(renderer_t* renderer);

void renderer_draw(GLuint vaoID, GLuint indexCount);

#endif // RENDERER_H
