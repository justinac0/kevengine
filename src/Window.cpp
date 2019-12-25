#include "Window.h"

/*********************************************************************/

static inline void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

static inline void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

static inline void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {}

static inline void glfw_cursor_enter_callback(GLFWwindow* window, int entered) {}

// soon we will want our own frame buffer to manage ourselfs
static inline void glfw_framebuffer_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

/*********************************************************************/

Window::Window(uint32_t width, uint32_t height, const char* title) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {}

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_SAMPLES, 4);

    this->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!this->handle) {}

    glfwMakeContextCurrent(this->handle);

    glfwSetKeyCallback(this->handle, glfw_key_callback);
    glfwSetMouseButtonCallback(this->handle, glfw_mouse_button_callback);
    glfwSetCursorEnterCallback(this->handle, glfw_cursor_enter_callback);
    glfwSetFramebufferSizeCallback(this->handle, glfw_framebuffer_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {}

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Window::~Window() {
    glfwDestroyWindow(this->handle);
    glfwTerminate();
}

GLFWwindow* Window::getHandle() {
    return this->handle;
}
