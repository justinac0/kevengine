#include "window.h"

void __framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* window_create(unsigned int width, unsigned int height, const char* title) {
    if (!glfwInit()) {}

    GLFWwindow* window = glfwCreateWindow(width, height, title, 0, 0);
    if (window == NULL) {}

    glfwSetFramebufferSizeCallback(window, __framebuffer_size_callback);

    glfwMakeContextCurrent(window);

    glViewport(0, 0, width, height);

    return window;
}

void window_destroy(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void window_update(GLFWwindow* window) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int window_get_request_close(GLFWwindow* window) {
    return glfwWindowShouldClose(window);
}

vec2_t window_get_size(GLFWwindow* window) {
    unsigned int width, height;

    glfwGetWindowSize(window, &width, &height);
    
    vec2_t size = { width, height };

    return size;
}

