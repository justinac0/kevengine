#define MEM_DEBUG
#include "core/util/mem.h"
#include "core/renderer/renderer.h"
#include "core/renderer/camera.h"
#include "core/renderer/entity.h"

// #include "../lib/lua-5.3.5/lua.h"
// #include "../lib/lua-5.3.5/lauxlib.h"
// #include "../lib/lua-5.3.5/lualib.h"

#include "../lib/cglm/include/cglm/cglm.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#include "core/util/str.h"

int main(void) {
    renderer_t renderer = renderer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Add to pool works! Need to make remove functions and add some casting macros.... (justin)
    mem_pool_t pool;
    mem_pool_create(&pool, sizeof(int) * 50+1);

    for (int i = 0; i < 50; i++) {
        mem_pool_block_add(&pool, mem_block_new(sizeof(int), (int*)i));
    }

    for (int i = 0; i < pool.length; i++) {
        printf("%d\n", pool.data[i].data);
    }

    printf("%d\n", 1010);

    mem_pool_destroy(&pool);

    printf("%d\n", 2020);


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
