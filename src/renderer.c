#include "renderer.h"

static inline void i_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

static inline void i_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static inline void i_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void r_context_create(r_context_t* renderer, uint32_t width, uint32_t height, const char* title) {
    if (!glfwInit()) {}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    renderer->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!renderer->window) {}

    glfwSetErrorCallback(i_error_callback);
    glfwSetKeyCallback(renderer->window, i_key_callback);
    glfwSetFramebufferSizeCallback(renderer->window, i_framebuffer_size_callback);

    glfwMakeContextCurrent(renderer->window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}

void r_context_destroy(r_context_t* renderer) {
    glfwDestroyWindow(renderer->window);
    glfwTerminate();
}

void r_context_update(GLFWwindow* pWindow) {
    glfwSwapBuffers(pWindow);
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

GLuint r_vertex_buffer_create(void) {
    GLuint vaoID;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    return vaoID;
}

GLuint r_buffer_create_c(uint32_t size, GLchar* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint r_buffer_create_s(uint32_t size, GLshort* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint r_buffer_create_i(uint32_t size, GLuint* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint r_buffer_create_f(uint32_t size, GLfloat* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

void r_buffer_delete(GLuint* bufferObject) {
    glDeleteBuffers(1, bufferObject);
}

GLuint r_shader_compile(const char* fileLocation, const int shaderType) {
    GLuint shaderID = glCreateShader(shaderType);
    uint32_t result, length;

    char* source = u_file_read(fileLocation);
    length = strlen(source);

    glShaderSource(shaderID, 1, (const char**)&source, &length);
    glCompileShader(shaderID);
    free(source);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

        char* errorLog = (char*)malloc(length);

        glGetShaderInfoLog(shaderID, length, &result, errorLog);
        glDeleteShader(shaderID);

        fprintf(stderr, "Shader compilation failed: %s\n", errorLog);
        free(errorLog);

        return 0;
    }

    return shaderID;
}

GLuint r_shader_load(const char* vertexFileLocation, const char* fragmentFileLocation) {
    GLuint vertID = r_shader_compile(vertexFileLocation,   GL_VERTEX_SHADER);
    GLuint fragID = r_shader_compile(fragmentFileLocation, GL_FRAGMENT_SHADER);

    GLuint shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertID);
    glAttachShader(shaderProgramID, fragID);
    glLinkProgram(shaderProgramID);

    glDetachShader(shaderProgramID, vertID);
    glDetachShader(shaderProgramID, fragID);

    glDeleteShader(vertID);
    glDeleteShader(fragID);

    return shaderProgramID;
}

void r_shader_use(GLuint shaderProgramID) {
    glUseProgram(shaderProgramID);
}

r_mesh_t r_mesh_triangle_generate(void) {
    GLfloat vertices[9] = {
        -1, -1, 0,
         1, -1, 0,
         0,  1, 0
    };

    GLuint indices[3] = {
        0, 1, 2
    };

    r_mesh_t mesh;
    mesh.vboID = r_buffer_create_f(sizeof(vertices), vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint iboID = r_buffer_create_s(sizeof(indices), indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    mesh.iCount = (sizeof(indices) / sizeof(GLshort));

    return mesh;
}

r_mesh_t r_mesh_obj(const char* fileLocation) {
    GLfloat vertices[9] = {
        -1, -1, 0,
         1, -1, 0,
         0,  1, 0
    };

    GLuint* indices = malloc(sizeof(GLuint) * 3);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    FILE* fileStream;
    if (fileStream = fopen(fileLocation, "r") == NULL) {
        fprintf(stderr, "Failed to read .obj file: %s", fileLocation);
        return;
    }

    fclose;

    r_mesh_t mesh;
    mesh.vboID = r_buffer_create_f(sizeof(vertices), vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint iboID = r_buffer_create_s(sizeof(GLuint) * 3, indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    mesh.iCount = (sizeof(indices) / sizeof(GLshort));

    return mesh;
}