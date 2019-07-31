#include "renderer.h"
#include <time.h>
#include <stdlib.h>

renderer_t renderer_create(unsigned int width, unsigned int height) {
    renderer_t renderer;
    renderer.window = window_create(width, height, "");

    return renderer;
}

void renderer_destroy(renderer_t* renderer) {
    window_destroy(renderer->window);
}

void renderer_draw(GLuint vaoID, GLuint indexCount) {
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
