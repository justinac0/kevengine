#include "renderer.h"
#include "g_math.h"
#include "util.h"

#define DEBUG_BUILD
#ifdef DEBUG_BUILD
    #define VS_FILE_LOCATION "bin/shaders/vertex.glsl"
    #define FS_FILE_LOCATION "bin/shaders/fragment.glsl"
#else
    #define VS_FILE_LOCATION "shaders/vertex.glsl"
    #define FS_FILE_LOCATION "shaders/fragment.glsl"
#endif // DEBUG_BUILD

int main(void) {
    r_context_t renderer;
    r_context_create(&renderer, 800, 600, "kevin");

    uint32_t shaderProgramID = r_shader_load(VS_FILE_LOCATION, FS_FILE_LOCATION);

    GLuint vaoID = r_vertex_buffer_create();

    r_mesh_t mesh  = r_mesh_triangle_generate();

    glBindVertexArray(0);

    mat4_t mvp, perspective, view, model;

    mvp         = mat4_identity();
    perspective = mat4_identity();
    model       = mat4_identity();
    view        = mat4_identity();

    while (!glfwWindowShouldClose(renderer.window)) {
        r_context_update(renderer.window);

        mvp = mat4_mul(&perspective, &view);
        mvp = mat4_mul(&mvp, &model);

        mvp.m13 += sin(glfwGetTime());
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "mvp"), 1, GL_FALSE, &mvp.m00);

        r_shader_use(shaderProgramID);
        glBindVertexArray(vaoID);
        glDrawElements(GL_TRIANGLES, mesh.iCount, GL_UNSIGNED_SHORT, 0);
    }

    r_context_destroy(&renderer);
    return 0;
}
