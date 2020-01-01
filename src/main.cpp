#include "BufferUtil.h"
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Model.h"

int main(void) {
    Window window       = Window(1080, 720, "kevengine");
    Shader shader       = Shader("./bin/shaders/vertex.glsl", "./bin/shaders/fragment.glsl");
    Shader skyBoxShader = Shader("./bin/shaders/sb_vertex.glsl", "./bin/shaders/sb_fragment.glsl");
    Shader sunShader    = Shader("./bin/shaders/sun_vertex.glsl", "./bin/shaders/sun_fragment.glsl");
    Camera camera       = Camera(1.0f, 5.0f);

    Model model = Model("./bin/models/terrain.obj");
    Model skybox = Model("./bin/models/sphere.obj");
    Model sun = Model("./bin/models/sphere.obj");
    sun.move(400, 6500, -400);
    sun.setScale(500, 500, 500);

    while (!glfwWindowShouldClose(window.getHandle())) {
        glfwPollEvents();
        glfwSwapBuffers(window.getHandle());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update();

        // draw gradient skybox
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        skyBoxShader.use();
        skyBoxShader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
        skyBoxShader.sendUniformMat4("view", glm::mat4(glm::mat3(camera.getViewMatrix())));
        skybox.render();


        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);

        // draw sun
        sunShader.use();
        sunShader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
        sunShader.sendUniformMat4("view", camera.getViewMatrix());
        sunShader.sendUniformMat4("model", sun.getMatrix());
        sun.render();

        // draw terrain
        shader.use();
        shader.sendUniformVec3("lightPosition", sun.getPosition());
        shader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
        shader.sendUniformMat4("view", camera.getViewMatrix());
        shader.sendUniformMat4("model", model.getMatrix());
        model.render();
    }

    return 0;
}
