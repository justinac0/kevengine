#include "game.h"

GLuint      shaderProgramID;
GLuint      vaoID;
r_mesh_t    mesh;
mat4_t      mvp;

void g_create(void) {
    m_mat4_identity(&mvp);
    m_mat4_print(&mvp);

    shaderProgramID = r_shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");
    vaoID = r_vertex_buffer_create();
    mesh = r_mesh_obj("bin/models/teapot.obj");
}

void g_destroy(void) {

}

void g_update(void) {

}

void g_render(void) {
    r_shader_use(shaderProgramID);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "mvp"), 1, GL_FALSE, &mvp.array[0][0]);
    r_mesh_draw(&mesh);
}
