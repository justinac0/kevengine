#include "game.h"

GLuint      shaderProgramID;
GLuint      vaoID;
r_mesh_t    meshes[2];
mat4_t      mvp, view, perspective;

void g_create(void) {
    shaderProgramID = r_shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");
    vaoID           = r_vertex_buffer_create();

    meshes[0] = r_mesh_obj("bin/models/cube.obj");
    meshes[1] = r_mesh_obj("bin/models/teapot.obj");

    m_perspective(&perspective, 45, 4/3, -0.01f, 100.0f);
    m_look_at(&view,
        (vec3_t){ 0, 0, 3 },
        (vec3_t){ 0, 0, 0 },
        (vec3_t){ 0, 1, 0 }
    );

    m_mat4_identity(&mvp);
    m_mat4_mul(&mvp, perspective, view);
}

void g_destroy(void) {

}

void g_update(void) {
    m_translate(&meshes[0].modelMatrix, cosf(glfwGetTime()), 0, sinf(glfwGetTime()));
    m_rotate_z(&meshes[1].modelMatrix, glfwGetTime() * RAD2DEG);
}

void g_render(void) {
    r_shader_use(shaderProgramID);
    for (int i = 0; i < 2; i++) {
        m_mat4_mul(&mvp, perspective, view);
        m_mat4_mul(&mvp, mvp, meshes[i].modelMatrix);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "mvp"), 1, GL_FALSE, &mvp.m00);
        r_mesh_draw(&meshes[i]);
    }
}
