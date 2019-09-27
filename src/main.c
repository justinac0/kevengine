#define U_MEM_DEBUG

#define DEBUG_BUILD
#ifdef DEBUG_BUILD
    #define VS_FILE_LOCATION "bin/shaders/vertex.glsl"
    #define FS_FILE_LOCATION "bin/shaders/fragment.glsl"
#else
    #define VS_FILE_LOCATION "shaders/vertex.glsl"
    #define FS_FILE_LOCATION "shaders/fragment.glsl"
#endif // DEBUG_BUILD

#include "util.h"
#include "renderer.h"
#include "linmath.h"

int main(int argc, char* argv[]) {
    r_context_t renderer;
    r_context_create(&renderer, 800, 600, "kevin");

    uint32_t shaderProgramID = r_shader_load(VS_FILE_LOCATION, FS_FILE_LOCATION);

    GLuint vaoID = r_vertex_buffer_create();

    r_mesh_t mesh = r_mesh_obj("bin/models/monkey.obj");

    glBindVertexArray(0);

    mat4x4 mvp, view, projection;

    mat4x4_look_at(view, (vec3){ 0, 0, 3 }, (vec3){ 0, 0, 0 }, (vec3){ 0, 1, 0 });
    mat4x4_perspective(projection, 45, 4 / 3, 0.01, 100);

    while (!glfwWindowShouldClose(renderer.window)) {
        r_context_update(renderer.window);

        mat4x4_mul(mvp, projection, view);
        mat4x4_mul(mvp, mvp, mesh.modelMatrix);

        mat4x4_rotate_Y(mesh.modelMatrix, mesh.modelMatrix, 0.05f);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "mvp"), 1, GL_FALSE, &mvp[0][0]);

        r_shader_use(shaderProgramID);
        glBindVertexArray(vaoID);
        glDrawElements(GL_TRIANGLES, mesh.iCount, GL_UNSIGNED_INT, 0);
    }

    r_context_destroy(&renderer);
    return 0;
}
