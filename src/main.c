#include "game.h"

#include "../deps/glad/glad.h"
#include <GLFW/glfw3.h>

#define FPS 120

int main(int argc, char* argv[]) {
    if (!glfwInit()) {}

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "kevin", NULL, NULL);

    if (!window) {}

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    g_create();

    double lastTime = glfwGetTime();
    double tickTime = 1.0f / FPS;

    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();

        if (glfwGetTime() >= lastTime + tickTime) {
            lastTime = glfwGetTime();
            g_update();
        }

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.2f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glCullFace(GL_FRONT_AND_BACK);
        g_render();
    }

    g_destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
