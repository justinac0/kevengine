#include "core/util/list.h"
#include "core/renderer/renderer.h"
#include "core/renderer/camera.h"
#include "core/renderer/entity.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

int main(void) {
    renderer_t renderer = renderer_create(WINDOW_WIDTH, WINDOW_HEIGHT);
    list_fixed_t integers = list_fixed_create(sizeof(int), 10);
    list_fixed_free(&integers);

    camera_t camera = camera_create(
        (vec3_t){ 0.0f, 0.0f, 3.0f },
        (vec3_t){ 0.0f, 0.0f,-1.0f },
        (vec3_t){ 0.0f, 1.0f, 0.0f }
    );

    mesh_t m1 = ogl_quad_generate(1.0f, (vec3_t){ 0, 1, 1 });
    mesh_t m2 = ogl_triangle_generate(1.0f);
    mesh_t m3 = ogl_cube_generate(1.0f);

    mat4_translate(&m2.tMatrix, (vec3_t){ 2.5f, 0, 0 });
    mat4_translate(&m3.tMatrix, (vec3_t){ 2.5f, 2.5f, 0 });

    mesh_t mm[3] = {m1, m2, m3};

    GLuint shader = shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");

    mat4_t perspective;
    mat4_t mvp;

    mat4_projection(&perspective, 90, 4/3, -1, 1000);

    mat4_t a;
    mat4_identity(&a);
    while (!glfwWindowShouldClose(renderer.window)) {
        ogl_clear(0.1f, 0.1f, 0.1f, 1.0f);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        camera_update(&camera);

        glUseProgram(shader);
        for (int i = 0; i < 3; i++) {
            glUniformMatrix4fv(glGetUniformLocation(shader, "mvp"), 1, GL_FALSE, &mvp.m00);

            mat4_mul(&mvp, perspective, camera.vMatrix);
            mat4_mul(&mvp, mvp, mm[i].tMatrix);

            glBindVertexArray(mm[i].vaoID);

            renderer_draw(mm[i].vaoID, mm[i].iCount);
        }

        window_update(renderer.window);
    }

    renderer_destroy(&renderer);

    return 0;
}
