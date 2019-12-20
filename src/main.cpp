#include "BufferUtil.h"
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Model.h"

int main(void) {
    Window window   = Window(800, 600, "kevengine");
    Shader shader   = Shader("./bin/shaders/vertex.glsl", "./bin/shaders/fragment.glsl");
    Camera camera   = Camera(0.05f, 0.05f);
    Model model     = Model("./bin/models/sword.obj");

    while (!glfwWindowShouldClose(window.getHandle())) {
        glfwPollEvents();
        glfwSwapBuffers(window.getHandle());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.freeMove();

        shader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
        shader.sendUniformMat4("view", camera.getViewMatrix());
        shader.sendUniformMat4("model", model.getMatrix());

        shader.sendUniformVec3("lightPosition", camera.getPosition());

        shader.use();
        model.update();
        model.render();
    }

    return 0;
}
