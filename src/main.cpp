#include "BufferUtil.h"
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main(void) {
    Window window   = Window(1080, 720, "kevengine");
    Shader shader   = Shader("./bin/shaders/vertex.glsl", "./bin/shaders/fragment.glsl");
    Camera camera   = Camera(1.0f, 0.5f);

    Model model     = Model("./bin/models/keyboard/keyboard.obj", "./bin/models/keyboard/");
    Texture thing   = Texture("./bin/models/keyboard/gray_concrete.png");
 
    while (!glfwWindowShouldClose(window.getHandle())) {
        glfwPollEvents();
        glfwSwapBuffers(window.getHandle());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.dragMouse();

        shader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
        shader.sendUniformMat4("view", camera.getViewMatrix());
        shader.sendUniformVec3("lightPosition", camera.getPosition());

        thing.use();
        shader.use();

        shader.sendUniformMat4("model", model.getMatrix());
        model.render();
    }

    return 0;
}
