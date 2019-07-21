#include "core/renderer/renderer.h"
#include "core/renderer/entity.h"

#include <stdbool.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

int main(void) {
    renderer_t renderer = renderer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    entity_t entity0 = entity_create(
        (vec3_t){ 0, 0, 0 },
        (vec3_t){ 0, 0, 0 },
        (vec3_t){ 1, 1, 1 },
        ogl_quad_generate()
    );

    entity_t entity1 = entity_create(
        (vec3_t){ 0, 0, 0 },
        (vec3_t){ 0, 0, 0 },
        (vec3_t){ 1, 1, 1 },
        ogl_quad_generate()
    );

    entity_t e[2] = { entity0, entity1 };

    GLuint shader = shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");

    static mat4_t perspective, view, mvp;
    vec3_t position = { 0, 0, 3 };
    vec3_t forward  = { 0, 0,-1 };
    vec3_t up       = { 0, 1, 0 };

    while (!glfwWindowShouldClose(renderer.window)) {
        window_update(renderer.window);
        ogl_clear(0.1f, 0.1f, 0.1f, 1.0f);

        mat4_projection(&perspective, 45, 1, -1, 1000);
        mat4_look_at(&view, position, vec3_add(position, forward), up);

        mat4_mul(&mvp, perspective, view);
        mat4_mul(&mvp, mvp, entity0.mesh.tMatrix);

        glUniformMatrix4fv(glGetUniformLocation(shader, "mvp"), 1, GL_FALSE, &mvp.m00);

        glUseProgram(shader);

        glBindVertexArray(entity0.mesh.vaoID);
        glDrawElements(GL_TRIANGLES, entity0.mesh.iCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        entity0.position.x = sin(glfwGetTime());
        entity1.position.y = sin(glfwGetTime());

        entity_update(&entity0);
        entity_update(&entity1);
    }

    renderer_destroy(&renderer);

    return 0;
}
