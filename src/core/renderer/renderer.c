#include "renderer.h"
#include <time.h>
#include <stdlib.h>

static mat4_t perspective;
static mat4_t mvp;

renderer_t renderer_create(unsigned int width, unsigned int height) {
    renderer_t renderer;
    renderer.window = window_create(width, height, "");
    mat4_projection(&perspective, 90, 4/3, -1, 1000);

    srand(time(NULL));

    return renderer;
}

void renderer_destroy(renderer_t* renderer) {
    window_destroy(renderer->window);
}

void renderer_draw(camera_t* camera, entity_t* e, GLuint shaderProgramID) {
        ogl_clear(0.1f, 0.1f, 0.1f, 1.0f);

        glUseProgram(shaderProgramID);

        for (int i = 0; i < 3; i++) {
            entity_update(&e[i]);

            float r = (float)rand()/(float)(RAND_MAX/1);
            float g = (float)rand()/(float)(RAND_MAX/1);
            float b = (float)rand()/(float)(RAND_MAX/1);

            glEnableVertexAttribArray(0);
            mat4_mul(&mvp, perspective, camera->vMatrix);
            mat4_mul(&mvp, mvp, e[i].mesh.tMatrix);

            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "mvp"), 1, GL_FALSE, &mvp.m00);
            glUniform3fv(glGetUniformLocation(shaderProgramID, "color"), 1, (float[3]){ r, g, b});

            glBindVertexArray(e[i].mesh.vaoID);
            glDrawElements(GL_TRIANGLES, e[i].mesh.iCount, GL_UNSIGNED_INT, 0);
        }
}