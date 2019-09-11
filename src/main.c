#define MEM_DEBUG
#include "core/util/mem.h"
#include "core/renderer/renderer.h"
#include "core/renderer/camera.h"
#include "core/renderer/entity.h"

#include "../deps/cglm/include/cglm/cglm.h"
#include "core/util/g_math.h"

const int WINDOW_WIDTH  = 1280;
const int WINDOW_HEIGHT = 720;

int main(void) {
    renderer_t renderer = renderer_create(WINDOW_WIDTH, WINDOW_HEIGHT);
    camera_t camera = camera_create();
    GLuint shader = shader_load("shaders/vertex.glsl", "shaders/fragment.glsl");

    entity_t e1 = entity_create(vec3_zero(), vec3_zero(), vec3_fill(1.f), ogl_triangle_generate(1.0f));

    mat4_t a = {
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2
    };

    mat4_t b = {
        3, 3, 3, 3,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2
    };

    mat4_t c = mat4_mul(&a, &b);
    mat4_print(&c);

    mat4 perspective, mvp;
    glm_perspective(75, window_size_get(renderer.window).x / window_size_get(renderer.window).y, 0.01f, 1024.0f, perspective);

    glm_translate(e1.mesh.modelMatrix, (vec3){0, 0, -5 });

    double lastTime = glfwGetTime();
    double timePerTick = 1.0f / 60.0f;

    while (!glfwWindowShouldClose(renderer.window)) {
        window_update(renderer.window);

        if (glfwGetTime() >= lastTime + timePerTick) {
            lastTime = glfwGetTime();

            camera_drag(&camera);

            for (int i = 0; i < 2; i++) {
                glm_mat4_mul(perspective, camera.viewMatrix, mvp);
                glm_mat4_mul(mvp, e1.mesh.modelMatrix, mvp);
                glUniformMatrix4fv(glGetUniformLocation(shader, "mvp"), 1, GL_FALSE, &mvp[0][0]);
            }
        }

        ogl_clear(0.1f, 0.1f, 0.1f, 1.0f);
        glUseProgram(shader);
        renderer_draw(e1.mesh.vaoID, e1.mesh.iCount);
    }

    renderer_destroy(&renderer);
    return 0;
}
