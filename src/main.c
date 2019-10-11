#include "kevin.h"

#define FPS 120

int main(int argc, char* argv) {
    GLFWwindow* pWindow = window_create(800, 600, "kevin");

    GLuint shaderProgramID, lightShaderProgramID;
    model_t models[2];
    mat4_t projection, view;

    shaderProgramID         = ogl_shader_load("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");
    lightShaderProgramID    = ogl_shader_load("bin/shaders/vs_light.glsl", "bin/shaders/fs_light.glsl");

    models[0] = model_create(mesh_wavefront_load("bin/models/dragon.obj"));
    models[1] = model_create(mesh_primitive_triangle());

    projection = m_projection(45, 4/3, 0.01f, 1000.0f);

    view = m_lookat(
        (vec3_t){ 0.0f, 0.0f, 3.0f },
        (vec3_t){ 0.0f, 0.0f, 0.0f },
        (vec3_t){ 0.0f, 1.0f, 0.0f }
    );

    models[0].position = (vec3_t){ 0, -2.5, -15 };

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(pWindow)) {
        window_update(pWindow);

        double currentTime = glfwGetTime();

        if (currentTime >= lastTime + 1.0f / FPS) {
            for (int i = 0; i < 2; i++) {
                model_update(&models[i]);
            }

            lastTime = glfwGetTime();

            models[1].position.y = 25 * sinf(glfwGetTime());
            models[1].position.z = 25 * cosf(glfwGetTime());
        }

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

        for (int i = 0; i < 2; i++) {
            ogl_shader_uniform_vec3(shaderProgramID, "lightPosition", &(vec3_t){ models[1].modelMatrix.m03, models[1].modelMatrix.m13, models[1].modelMatrix.m23 });

            if (i == 1) {
                ogl_shader_use(lightShaderProgramID);
                ogl_shader_uniform_mat4(lightShaderProgramID, "projection", &projection);
                ogl_shader_uniform_mat4(lightShaderProgramID, "view", &view);
                ogl_shader_uniform_mat4(lightShaderProgramID, "model", &models[i].modelMatrix);
                ogl_draw(GL_TRIANGLES, models[i].mesh.vaoID, models[i].mesh.iCount);
            } else {
                ogl_shader_use(shaderProgramID);
                ogl_shader_uniform_mat4(shaderProgramID, "projection", &projection);
                ogl_shader_uniform_mat4(shaderProgramID, "view", &view);
                ogl_shader_uniform_mat4(shaderProgramID, "model", &models[i].modelMatrix);
                ogl_draw(GL_TRIANGLES, models[i].mesh.vaoID, models[i].mesh.iCount);
            }
        }

    }

    window_destroy(pWindow);

    return 0;
}
