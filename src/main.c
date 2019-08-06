#define MEM_DEBUG
#include "core/util/mem.h"
#include "core/renderer/renderer.h"
#include "core/renderer/camera.h"
#include "core/renderer/entity.h"

#include "../lib/lua-5.3.5/lua.h"
#include "../lib/lua-5.3.5/lauxlib.h"
#include "../lib/lua-5.3.5/lualib.h"

#include "../lib/cglm/include/cglm/cglm.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

int main(void) {
    mem_pool_t pool;
    mem_pool_create(&pool, 10);

    mem_pool_destroy(&pool);

    renderer_t renderer = renderer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    camera_t camera = camera_create(
        (vec3){ 0.0f, 0.0f, 3.0f },
        (vec3){ 0.0f, 0.0f,-1.0f },
        (vec3){ 0.0f, 1.0f, 0.0f }
    );

    GLuint shader = shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");
    mesh_t m[2] = {
        ogl_triangle_generate(1),
        ogl_cube_generate(2)
    };

    mat4 perspective, mvp, view;
    glm_perspective(45, 4/3, 0.01f, 1024.0f, perspective);

    glm_translate(m[0].modelMatrix, (vec3){0, 4, -10});
    glm_translate(m[1].modelMatrix, (vec3){0, -1, -10});

    while (!glfwWindowShouldClose(renderer.window)) {
        window_update(renderer.window);

        glm_rotate(m[1].modelMatrix, 0.01f, (vec3){0, 0.01f, 0});
        camera_update(&camera);

        ogl_clear(0.1f, 0.1f, 0.1f, 1.0f);

        glUseProgram(shader);
        for (int i = 0; i < 2; i++) {
            glm_mat4_mul(perspective, camera.viewMatrix, mvp);
            glm_mat4_mul(mvp, m[i].modelMatrix, mvp);
            glUniformMatrix4fv(glGetUniformLocation(shader, "mvp"), 1, GL_FALSE, &mvp[0][0]);

            renderer_draw(m[i].vaoID, m[i].iCount);
        }
    }

    renderer_destroy(&renderer);

    return 0;
}
