#include "opengl_helper.h"

GLuint ogl_vertex_buffer_create(void) {
    GLuint vaoID;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    return vaoID;
}

GLuint ogl_buffer_create_c(uint32_t size, GLchar* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint ogl_buffer_create_s(uint32_t size, GLshort* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint ogl_buffer_create_i(uint32_t size, GLuint* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint ogl_buffer_create_f(uint32_t size, GLfloat* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

void ogl_buffer_delete(GLuint* bufferObject) {
    glDeleteBuffers(1, bufferObject);
}


GLuint ogl_shader_compile(const char* fileLocation, const int shaderType) {
    GLuint shaderID = glCreateShader(shaderType);
    uint32_t result, length;

    const char* source = u_file_read(fileLocation);
    length = strlen(source);

    glShaderSource(shaderID, 1, &source, &length);
    glCompileShader(shaderID);

    free(source);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

        char* errorLog = (char*) malloc(length + 1);

        glGetShaderInfoLog(shaderID, length, &result, errorLog);
        glDeleteShader(shaderID);

        fprintf(stderr, "Shader compilation failed: %s\n", errorLog);
        
        free(errorLog);

        return 0;        
    }

    return shaderID;
}

GLuint ogl_shader_load_default(void) {}

GLuint ogl_shader_load(const char* vsFileLocation, const char* fsFileLocation) {
    GLuint vertID = ogl_shader_compile(vsFileLocation, GL_VERTEX_SHADER);
    GLuint fragID = ogl_shader_compile(fsFileLocation, GL_FRAGMENT_SHADER);

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

void ogl_shader_use(GLuint programID) {
    glUseProgram(programID);
}

inline void ogl_shader_uniform_vec3(GLfloat programID, const char* name, vec3_t* vector) {
        glUniform3f(glGetUniformLocation(programID, name), vector->x, vector->y, vector->z);
}

inline void ogl_shader_uniform_mat4(GLfloat programID, const char* name, mat4_t* matrix) {
    glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, &matrix->m00);
}

void ogl_draw(const int drawType, GLuint vaoID, uint32_t iCount) {
    glBindVertexArray(vaoID);
    glDrawElements(drawType, iCount, GL_UNSIGNED_INT, NULL);
}
