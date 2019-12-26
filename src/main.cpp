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

    Model skull     = Model("./bin/models/craneo/craneo.OBJ");
    Texture thing   = Texture("./bin/models/craneo/textures/difuso_flip_oscuro_5.jpg");

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

        shader.sendUniformMat4("model", skull.getMatrix());
        skull.render();
    }

    return 0;
}
