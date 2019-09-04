#define MEM_DEBUG
#include "core/util/mem.h"
#include "core/renderer/renderer.h"
#include "core/renderer/camera.h"
#include "core/renderer/entity.h"

#include "../lib/cglm/include/cglm/cglm.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define LEN 30

int main(void) {
    renderer_t renderer = renderer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    camera_t camera = camera_create(
        (vec3){ 0.0f, 0.0f, 3.0f },
        (vec3){ 0.0f, 0.0f,-1.0f },
        (vec3){ 0.0f, 1.0f, 0.0f }
    );

    GLuint shader = shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");
    mesh_t m = ogl_cube_generate(1.0f);

    mat4 perspective, mvp, view;
    glm_perspective(45, 4/3, 0.01f, 1024.0f, perspective);

    glm_translate(m.modelMatrix, (vec3){0, 0, -5 });

    double lastTime = glfwGetTime();
    double timePerTick = 1.0f / 60.0f;
    while (!glfwWindowShouldClose(renderer.window)) {
        window_update(renderer.window);

        if (glfwGetTime() >= lastTime + timePerTick) {
            lastTime = glfwGetTime();

            camera_drag(&camera);

            for (int i = 0; i < 2; i++) {
                glm_mat4_mul(perspective, camera.viewMatrix, mvp);
                glm_mat4_mul(mvp, m.modelMatrix, mvp);
                glUniformMatrix4fv(glGetUniformLocation(shader, "mvp"), 1, GL_FALSE, &mvp[0][0]);
            }
        }

        ogl_clear(0.1f, 0.1f, 0.1f, 1.0f);
        glUseProgram(shader);
        renderer_draw(m.vaoID, m.iCount);
    }

    renderer_destroy(&renderer);
    return 0;
}
