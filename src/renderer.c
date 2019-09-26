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
    FILE* fileStream = fopen(fileLocation, "r");
    if (fileStream == NULL) {
        fprintf(stderr, "Failed to find file: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    uint32_t vCount = 0;
    float v1,v2,v3;

    uint32_t fCount = 0;
    int f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12;

    while (fgetc(fileStream) != EOF) {
        if (fscanf(fileStream, "v %f %f %f", &v1, &v2, &v3) == 3) {
            vCount += 3;
        }

        if (fscanf(fileStream, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9, &f10, &f11, &f12) == 12) {
            fCount += 12;
        }
    }

    rewind(fileStream);

    GLfloat* verts  = (GLfloat*)malloc(sizeof(float) * vCount);
    GLuint* inds    = (GLuint*)malloc(sizeof(GLuint) * fCount);

    uint32_t vP = 0;
    uint32_t fP = 0;
    
    while (fgetc(fileStream) != EOF) {
        if (fscanf(fileStream, "v %f %f %f", &v1, &v2, &v3) == 3) {
            verts[vP]   = v1;
            verts[vP+1] = v2;
            verts[vP+2] = v3;

            vP += 3;
        }

        if (fscanf(fileStream, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9, &f10, &f11, &f12) == 12) {
            inds[fP]    = f1;
            inds[fP+1]  = f2;
            inds[fP+2]  = f3;
            inds[fP+3]  = f4;
            inds[fP+4]  = f5;
            inds[fP+5]  = f6;
            inds[fP+6]  = f7;
            inds[fP+7]  = f8;
            inds[fP+8]  = f9;
            inds[fP+9]  = f10;
            inds[fP+10] = f11;
            inds[fP+11] = f12;

            fP += 12;
        }
    }

    printf("vLn: %d\n", vCount);
    printf("fLn: %d\n", fCount);

    if (fclose(fileStream) != 0) {
        fprintf(stderr, "File was not closed properly: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vCount/3; i++) {
        printf("%f %f %f\n", verts[i], verts[i+1], verts[i+2]);
    }

    for (int i = 0; i < fCount; i++) {
        printf("%d\n", inds[i]);
    }

    r_mesh_t mesh;
    mesh.vboID = r_buffer_create_f(sizeof(float) * vCount, verts, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint iboID = r_buffer_create_i(sizeof(GLuint) * fCount, inds, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    mesh.iCount = fCount;

    free(verts);
    free(inds);

    return mesh;
}

    // //Mitch's function start


    // FILE* fileStream;
    // if ((fileStream = fopen(fileLocation, "r")) == NULL) {
    //     fprintf(stderr, "Failed to read file: %s\n", fileLocation);
    //     return;
    // }

    // GLfloat*    verts;
    // uint32_t    vertLength;

    // GLuint*     faces;
    // uint32_t    faceLength;

    // float a1 = 0;
    // float a2;
    // float a3;
    // float a4;
    // float a5;
    // float a6;
    // float a7;
    // float a8;
    // float a9;
    // float a10;
    // float a11;
    // float a12;

    // uint32_t vCount = 0;
    // uint32_t fCount = 0;

    // // First iteration -> get n of 'v' and 'f'
    // fscanf(fileStream, "# Blender v%f", &a1);
    // printf("Value: %f\n", a1);

    // float a,b,c;
    // fscanf(fileStream, "v %f %f %f", &a, &b, &c);
    // printf("xyz: %f %f %f\n", a, b, c);

    // while (fscanf(fileStream, "v %f %f %f\n", &a1, &a2, &a3) == 3) {
    //    vCount++;
    // }

    // while (fscanf(fileStream, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10, &a11, &a12) == 12) {
    //    fCount++;
    // }

    // while (fscanf(fileStream, "v %f %f %f\n") == 3) {

    // }

    // printf("Vertice Count:\t%d\nFace Count:\t%d\n", vCount, fCount);

    // fclose(fileStream);

    // //Mitch's function end