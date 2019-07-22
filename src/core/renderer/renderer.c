#include "renderer.h"


static mat4_t perspective;
static mat4_t view;
static mat4_t mvp;

static vec3_t position;
static vec3_t forward;
static vec3_t up;

renderer_t renderer_create(unsigned int width, unsigned int height) {
    renderer_t renderer;
    renderer.window = window_create(width, height, "");

    position    = (vec3_t){ 0, 0, 3 };
    forward     = (vec3_t){ 0, 0,-1 };
    up          = (vec3_t){ 0, 1, 0 };

    return renderer;
}

void renderer_destroy(renderer_t* renderer) {
    window_destroy(renderer->window);
}

void renderer_draw(entity_t* e, GLuint shaderProgramID) {
        ogl_clear(0.1f, 0.1f, 0.1f, 1.0f);

        glUseProgram(shaderProgramID);
        glEnableVertexAttribArray(0);

        mat4_projection(&perspective, 45, 1, -1, 1000);
        mat4_look_at(&view, position, vec3_add(position, forward), up);

        for (int i = 0; i < 2; i++) {
            entity_update(&e[i]);

            mat4_mul(&mvp, perspective, view);
            mat4_mul(&mvp, mvp, e[i].mesh.tMatrix);

            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "mvp"), 1, GL_FALSE, &mvp.m00);

            glBindVertexArray(e[i].mesh.vaoID);
            glDrawElements(GL_TRIANGLES, e[i].mesh.iCount, GL_UNSIGNED_INT, 0);
        }

        glBindVertexArray(0);
        glUseProgram(0);
}