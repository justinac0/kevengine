#include "kevin.h"

int main(int argc, char* argv) {
    GLFWwindow* pWindow = window_create(800, 600, "kevin");

    GLuint shaderProgramID, lightShader;
    mesh_t meshes[2];
    mat4x4 mvp, view, projection;

    shaderProgramID = shader_load("shaders/vertex.glsl", "shaders/fragment.glsl");
    lightShader     = shader_load("shaders/vs_light.glsl", "shaders/fs_light.glsl");

    meshes[0] = mesh_wavefront_load("models/sphere.obj");
    meshes[1] = mesh_wavefront_load("models/sphere.obj");

    mat4x4_perspective(projection, 20, 16 / 9, 0.01f, 100.0f);
    mat4x4_look_at(view,
        (vec3){ 0.0f, 0.0f, 3.0f },
        (vec3){ 0.0f, 0.0f, 0.0f },
        (vec3){ 0.0f, 1.0f, 0.0f }
    );

    mat4x4_translate(view, 0, 0, -30);

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(pWindow)) {
        window_update(pWindow);

        if (glfwGetTime() >= lastTime + 1.0f / 120) {
            lastTime = glfwGetTime();
            
            // update
            mat4x4_translate(meshes[0].modelMatrix.v, 0, 2.5 * sinf(glfwGetTime()), 0);
            mat4x4_translate(meshes[1].modelMatrix.v, 5 * sinf(glfwGetTime()), 0.0f, 5 * cosf(glfwGetTime()));
        }

        // render
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.2f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                shader_use(shaderProgramID);
                glUniform3f(glGetUniformLocation(shaderProgramID, "lightPosition"), meshes[1].modelMatrix.m03, meshes[1].modelMatrix.m13, meshes[1].modelMatrix.m23);
                glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "projection"), 1, GL_FALSE, &projection[0][0]);
                glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view"), 1, GL_FALSE, &view[0][0]);
                glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, &meshes[i].modelMatrix.v);
            } else {
                shader_use(lightShader);
                glUniformMatrix4fv(glGetUniformLocation(lightShader, "projection"), 1, GL_FALSE, &projection[0][0]);
                glUniformMatrix4fv(glGetUniformLocation(lightShader, "view"), 1, GL_FALSE, &view[0][0]);
                glUniformMatrix4fv(glGetUniformLocation(lightShader, "model"), 1, GL_FALSE, &meshes[i].modelMatrix.v);
            }

            ogl_draw(GL_TRIANGLES, meshes[i].vaoID, meshes[i].iCount);
        }
    }

    window_destroy(pWindow);

    return 0;
}
