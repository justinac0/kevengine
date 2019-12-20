#include "BufferUtil.h"
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

int main(void) {
    Window window   = Window(800, 600, "kevengine");
    Shader shader   = Shader("./bin/shaders/vertex.glsl", "./bin/shaders/fragment.glsl");
    Camera camera   = Camera();

    std::vector<GLfloat> vertices = {
        -1, -1, 0,
         1, -1, 0,
         0,  1, 0
    };

    std::vector<GLfloat> colors = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };

    std::vector<GLuint> indices = {
        0, 1, 2
    };

    Mesh mesh = Mesh(vertices, colors, indices);

    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp;

    float i = 0;
    while (!glfwWindowShouldClose(window.getHandle())) {
        glfwPollEvents();
        glfwSwapBuffers(window.getHandle());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        camera.freeMove();

        mvp = camera.getPerspectiveMatrix() * camera.getViewMatrix() * Model;
        shader.sendUniformMat4("mvp", mvp);
        shader.use();
        mesh.draw();

    }

    return 0;
}
