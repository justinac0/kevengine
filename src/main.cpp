#include "BufferUtil.h"
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Model.h"

int main(void) {
    Window window   = Window(800, 600, "kevengine");
    Shader shader   = Shader("./bin/shaders/vertex.glsl", "./bin/shaders/fragment.glsl");
    Camera camera   = Camera(1.0f, 0.2f);

    Model modelsWorking[5] = {
        Model("./bin/models/sword.obj"),
        Model("./bin/models/sword.obj"),
        Model("./bin/models/sword.obj"),
        Model("./bin/models/sword.obj"),
        Model("./bin/models/sword.obj")
    };

    for (int i = 0; i < 5; i++) {
        modelsWorking[i].move(i, 0, 0);
    }

    std::vector<Model> modelsBroken = {
        Model("./bin/models/suzanne.obj"),
        Model("./bin/models/suzanne.obj"),
        Model("./bin/models/suzanne.obj"),
        Model("./bin/models/suzanne.obj"),
        Model("./bin/models/suzanne.obj")
    };

    for (int i = 0; i < 5; i++) {
        modelsBroken[i].move(i, 0, 0); // modelsBroken.at(index) is the same thing
    }

    while (!glfwWindowShouldClose(window.getHandle())) {
        glfwPollEvents();
        glfwSwapBuffers(window.getHandle());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update();

        for (int i = 0; i < 5; i++) {
            // WORKING WITH modelsWorking array
            // shader.use();
            // shader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
            // shader.sendUniformMat4("view", camera.getViewMatrix());
            // shader.sendUniformVec3("lightPosition", camera.getPosition());
            // shader.sendUniformMat4("model", modelsWorking[i].getMatrix());
            // modelsWorking[i].render();
        
            // WORKING WITH modelsWorking array
            shader.use();
            shader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
            shader.sendUniformMat4("view", camera.getViewMatrix());
            shader.sendUniformVec3("lightPosition", camera.getPosition());
            shader.sendUniformMat4("model", modelsBroken[i].getMatrix());
            modelsBroken[i].render();
        }

    }

    return 0;
}
