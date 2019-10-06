#include "game.h"

#include "core/renderer/window.h"

#define FPS 120

int main(int argc, char* argv) {
    GLFWwindow* pWindow = window_create(800, 600, "kevin");

    g_create();

    double lastTime = glfwGetTime();
    double tickTime = 1.0f / FPS;

    while (!glfwWindowShouldClose(pWindow)) {
        window_update(pWindow);

        if (glfwGetTime() >= lastTime + tickTime) {
            lastTime = glfwGetTime();
            g_update();
        }

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.2f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        g_render();
    }

    g_destroy();

    window_destroy(pWindow);

    return 0;
}
