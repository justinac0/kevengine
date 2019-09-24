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
#include "g_math.h"
#include "renderer.h"

int main(void) {
    r_context_t renderer;
    r_context_create(&renderer, 800, 600, "kevin");

    uint32_t shaderProgramID = r_shader_load(VS_FILE_LOCATION, FS_FILE_LOCATION);

    GLuint vaoID = r_vertex_buffer_create();

    r_mesh_t mesh  = r_mesh_triangle_generate();

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(renderer.window)) {
        r_context_update(renderer.window);

        r_shader_use(shaderProgramID);
        glBindVertexArray(vaoID);
        glDrawElements(GL_TRIANGLES, mesh.iCount, GL_UNSIGNED_INT, 0);
    }

    r_context_destroy(&renderer);
    return 0;
}
