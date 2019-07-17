#include "renderer.h"

renderer_t renderer_create(unsigned int width, unsigned int height) {
    renderer_t renderer;
    renderer.window = window_create(width, height, "");
    ogl_setup();

    return renderer;
}

void renderer_destroy(renderer_t* renderer) {
    window_destroy(renderer->window);
}
