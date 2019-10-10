#include "window.h"

// GLFWwindow internal callback functions
static inline void i_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

static inline void i_key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
    }
}

static inline void i_framebuffer_size_callback(GLFWwindow* pWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* window_create(uint32_t width, uint32_t height, const char* title) {
    // initialize the GLFW library
    if (!glfwInit()) {
        printf("Failed to initialize the GLFW library.\n");
        exit(EXIT_FAILURE);
    }

    // setup window hints
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!pWindow) {
        printf("Failed to create GLFWwindow.\n");
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(i_error_callback);
    glfwSetKeyCallback(pWindow, i_key_callback);
    glfwSetFramebufferSizeCallback(pWindow, i_framebuffer_size_callback);

    glfwMakeContextCurrent(pWindow);

    // load opengl extensions
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(1);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return pWindow;
}

void window_update(GLFWwindow* pWindow) {
    glfwSwapBuffers(pWindow);
    glfwPollEvents();
}

void window_destroy(GLFWwindow* pWindow) {
    glfwDestroyWindow(pWindow);
    glfwTerminate();
}

vec2_t window_get_size(GLFWwindow* pWindow) {
    double w, h;
    glfwGetWindowSize(pWindow, &w, &h);

    return (vec2_t){ w, h };
}
