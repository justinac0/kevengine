#include "ogl.h"

void ogl_setup(void) {
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void ogl_clear(float r, float g, float b, float a) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, a);
}

