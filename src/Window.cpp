#include "Window.h"

/*********************************************************************/

static inline void glfw_framebuffer_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

/*********************************************************************/

Window::Window(uint32_t width, uint32_t height, const char* title) {
    if (!glfwInit()) {}

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    this->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!this->handle) {}

    glfwMakeContextCurrent(this->handle);

    glfwSetFramebufferSizeCallback(this->handle, glfw_framebuffer_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {}

    glViewport(0, 0, width, height);
}

Window::~Window() {
    glfwDestroyWindow(this->handle);
    glfwTerminate();
}

GLFWwindow* Window::getHandle() {
    return this->handle;
}
