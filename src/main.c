#include "kevin.h"

#define FPS 120

int main(int argc, char* argv) {
    GLFWwindow* pWindow = window_create(800, 600, "kevin");

    GLuint shaderProgramID, lightShaderProgramID;
    mesh_t meshes[2];
    mat4x4 view;
    mat4_t projection;

    shaderProgramID         = ogl_shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");
    lightShaderProgramID    = ogl_shader_load("bin/shaders/vs_light.glsl", "bin/shaders/fs_light.glsl");

    meshes[0] = mesh_primitive_triangle();
    meshes[1] = mesh_primitive_triangle();

    projection = m_projection(45, 4/3, 0.01f, 1000.0f);

    mat4x4_look_at(view,
        (vec3){ 0.0f, 0.0f, 3.0f },
        (vec3){ 0.0f, 0.0f, 0.0f },
        (vec3){ 0.0f, 1.0f, 0.0f }
    );

    double lastTime = glfwGetTime();

    meshes[0].modelMatrix = m_translate((vec3_t){ 0, 0, -5 });

    while (!glfwWindowShouldClose(pWindow)) {
        window_update(pWindow);

        double currentTime = glfwGetTime();

        if (currentTime >= lastTime + 1.0f / FPS) {
            lastTime = glfwGetTime();

            // update
            mat4x4_translate(meshes[1].modelMatrix.v, 15 * sinf(glfwGetTime()), 5, 15 * cosf(glfwGetTime()));
        }

        // render
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

        for (int i = 0; i < 2; i++) {
            ogl_shader_uniform_vec3(shaderProgramID, "lightPosition", &(vec3_t){ meshes[1].modelMatrix.m03, meshes[1].modelMatrix.m13, meshes[1].modelMatrix.m23 });

            if (i == 1) {
                ogl_shader_use(lightShaderProgramID);
                ogl_shader_uniform_mat4(lightShaderProgramID, "projection", &projection);
                ogl_shader_uniform_mat4(lightShaderProgramID, "view", view);
                ogl_shader_uniform_mat4(lightShaderProgramID, "model", meshes[i].modelMatrix.v);
                ogl_draw(GL_TRIANGLES, meshes[i].vaoID, meshes[i].iCount);
            } else {
                ogl_shader_use(shaderProgramID);
                ogl_shader_uniform_mat4(shaderProgramID, "projection", &projection);
                ogl_shader_uniform_mat4(shaderProgramID, "view", view);
                ogl_shader_uniform_mat4(shaderProgramID, "model", meshes[i].modelMatrix.v);
                ogl_draw(GL_TRIANGLES, meshes[i].vaoID, meshes[i].iCount);
            }
        }

    }

    window_destroy(pWindow);

    return 0;
}
