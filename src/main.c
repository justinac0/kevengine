#include "core/renderer/renderer.h"

int main(void) {
    renderer_t renderer = renderer_create(800, 600);

    while (!window_get_request_close(renderer.window)) {
        window_update(renderer.window);

        ogl_clear(0.2, 0.2, 0.2, 1);
    }

    renderer_destroy(&renderer);

    return 0;
}
