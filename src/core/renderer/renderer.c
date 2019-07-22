#include "renderer.h"

static mat4_t perspective;
static mat4_t mvp;

renderer_t renderer_create(unsigned int width, unsigned int height) {
    renderer_t renderer;
    renderer.window = window_create(width, height, "");
    mat4_projection(&perspective, 90, 1, -1, 1000);

    return renderer;
}

void renderer_destroy(renderer_t* renderer) {
    window_destroy(renderer->window);
}

void renderer_draw(camera_t* camera, entity_t* e, GLuint shaderProgramID) {
        ogl_clear(0.1f, 0.1f, 0.1f, 1.0f);

        glUseProgram(shaderProgramID);

        for (int i = 0; i < 2; i++) {
            entity_update(&e[i]);

            glEnableVertexAttribArray(0);
            mat4_mul(&mvp, perspective, camera->vMatrix);
            mat4_mul(&mvp, mvp, e[i].mesh.tMatrix);

            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "mvp"), 1, GL_FALSE, &mvp.m00);

            glBindVertexArray(e[i].mesh.vaoID);
            glDrawElements(GL_TRIANGLES, e[i].mesh.iCount, GL_UNSIGNED_INT, 0);
        }
}