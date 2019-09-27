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

int main(int argc, char* argv[]) {
    r_context_t renderer;
    r_context_create(&renderer, 800, 600, "kevin");

    uint32_t shaderProgramID = r_shader_load(VS_FILE_LOCATION, FS_FILE_LOCATION);

    GLuint vaoID = r_vertex_buffer_create();

    r_mesh_t mesh = r_mesh_obj("bin/models/cube.obj");

    glBindVertexArray(0);

    mat4_t mvp = mat4_identity();


    while (!glfwWindowShouldClose(renderer.window)) {
        r_context_update(renderer.window);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "mvp"), 1, GL_FALSE, &mvp.v[0][0]);

        r_shader_use(shaderProgramID);
        glBindVertexArray(vaoID);

        glDrawElements(GL_TRIANGLES, mesh.iCount, GL_UNSIGNED_INT, 0);
    }

    r_context_destroy(&renderer);
    return 0;
}
