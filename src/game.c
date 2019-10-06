#include "game.h"
#include "math.h"

GLuint      shaderProgramID, lightShader;
r_mesh_t    meshes[2];
mat4x4      mvp, view, projection;
vec2_t a;

void g_create(void) {
    shaderProgramID = r_shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");
    lightShader = r_shader_load("bin/shaders/vs_light.glsl", "bin/shaders/fs_light.glsl");

    meshes[0] = r_mesh_obj("bin/models/sphere.obj");
    meshes[1] = r_mesh_obj("bin/models/sphere.obj");

    mat4x4_perspective(projection, 20, 16 / 9, 0.01f, 100.0f);
    mat4x4_look_at(view,
        (vec3){ 0.0f, 0.0f, 3.0f },
        (vec3){ 0.0f, 0.0f, 0.0f },
        (vec3){ 0.0f, 1.0f, 0.0f }
    );

    mat4x4_translate(view, 0, 0, -30);
}

void g_destroy(void) { }

void g_update(void) {
    mat4x4_translate(meshes[0].modelMatrix.v, 0, 2.5 * sinf(glfwGetTime()), 0);
    mat4x4_translate(meshes[1].modelMatrix.v, 5 * sinf(glfwGetTime()), 0.0f, 5 * cosf(glfwGetTime()));
}

void g_render(void) {
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            r_shader_use(shaderProgramID);
            glUniform3f(glGetUniformLocation(shaderProgramID, "lightPosition"), meshes[1].modelMatrix.m03, meshes[1].modelMatrix.m13, meshes[1].modelMatrix.m23);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "projection"), 1, GL_FALSE, &projection[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view"), 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, &meshes[i].modelMatrix.v);
            r_mesh_draw(&meshes[i]);
        } else {
            r_shader_use(lightShader);
            glUniformMatrix4fv(glGetUniformLocation(lightShader, "projection"), 1, GL_FALSE, &projection[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(lightShader, "view"), 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(lightShader, "model"), 1, GL_FALSE, &meshes[i].modelMatrix.v);
            r_mesh_draw(&meshes[i]);
        }
    }
}
