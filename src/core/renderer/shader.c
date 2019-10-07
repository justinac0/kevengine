#include "shader.h"

GLuint shader_compile(const char* fileLocation, const int shaderType) {
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

GLuint shader_load_default(void) {}

GLuint shader_load(const char* vsFileLocation, const char* fsFileLocation) {
    GLuint vertID = shader_compile(vsFileLocation, GL_VERTEX_SHADER);
    GLuint fragID = shader_compile(fsFileLocation, GL_FRAGMENT_SHADER);

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

void shader_use(GLuint programID) {
    glUseProgram(programID);
}
