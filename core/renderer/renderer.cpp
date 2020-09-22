#include "renderer.hpp"

using namespace kevin::renderer;

void _glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void _error_callback(int code, const char* description) {
    std::cout << "[GLFW ERROR](code,desc): " << std::endl << code << ", " << description << std::endl;
}

Renderer::Renderer(uint32_t width, uint32_t height) {
    glfwSetErrorCallback(_error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->m_Window = glfwCreateWindow(width, height, "kevengine", 0, 0);
    if (!this->m_Window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(this->m_Window, _glfwKeyCallback);
    glfwMakeContextCurrent(this->m_Window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
}

Renderer::~Renderer() {
    glfwTerminate();
}

void Renderer::UpdateWindow() {
    glfwPollEvents();
    glfwSwapBuffers(this->m_Window);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.2, 0.3, 1.0);
}

bool Renderer::GetWindowShouldClose() {
    return glfwWindowShouldClose(this->m_Window);
}

GLFWwindow* Renderer::GetWindowHandle() {
    return this->m_Window;
}
