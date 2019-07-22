#include "core/renderer/renderer.h"
#include "core/renderer/camera.h"
#include "core/renderer/entity.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

int main(void) {
    renderer_t renderer = renderer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    camera_t camera = camera_create(
        (vec3_t){ 0.0f, 0.0f, 3.0f },
        (vec3_t){ 0.0f, 0.0f,-1.0f },
        (vec3_t){ 0.0f, 1.0f, 0.0f }
    );

    entity_t entity0 = entity_create(
        (vec3_t){ 0.0f, 0.0f, 0.0f },
        (vec3_t){ 0.0f, 0.0f, 0.0f },
        (vec3_t){ 1.0f, 1.0f, 1.0f },
        ogl_cube_generate()
    );

    entity_t entity1 = entity_create(
        (vec3_t){ 0.0f, 0.0f, 0.0f },
        (vec3_t){ 0.0f, 0.0f, 0.0f },
        (vec3_t){ 1.0f, 1.0f, 1.0f },
        ogl_quad_generate()
    );

    entity_t e[2] = { entity0, entity1 };

    GLuint shader = shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");

    while (!glfwWindowShouldClose(renderer.window)) {
        window_update(renderer.window);

        e[0].position.z = sin(glfwGetTime());
        e[1].position.y = sin(glfwGetTime()) - 5;

        camera_update(&camera);
        renderer_draw(&camera, e, shader);

        glDisableVertexAttribArray(0);
    }

    renderer_destroy(&renderer);

    return 0;
}
