#include "Shader.h"

char* readFile(const char* path) {
    FILE* fileStream = fopen(path, "r");
    if (!fileStream) {}
    fseek(fileStream, 0, SEEK_END);
    uint32_t length = ftell(fileStream);
    rewind(fileStream);
    char* buffer = (char*) malloc(length + 1);
    fread(buffer, 1, length, fileStream);
    fclose(fileStream);

    return buffer; 
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    char* vertexSource = readFile(vertexShaderPath);
    this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(this->vertexShaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(this->vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->vertexShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    char* fragmentSource = readFile(fragmentShaderPath);
    this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(this->fragmentShaderID);

    glGetShaderiv(this->fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(this->fragmentShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    this->programID = glCreateProgram();
    glAttachShader(this->programID, this->vertexShaderID);
    glAttachShader(this->programID, this->fragmentShaderID);
    glLinkProgram(this->programID);

    glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(this->vertexShaderID);
    glDeleteShader(this->fragmentShaderID);

    free(vertexSource);
    free(fragmentSource);
}

Shader::~Shader(void) {
    glDeleteProgram(this->programID);
}

void Shader::use(void) {
    glUseProgram(this->programID);
}

void Shader::sendUniformMat4(const GLchar* name, glm::mat4 src) {
    glUniformMatrix4fv(glGetUniformLocation(this->programID, name), 1, GL_FALSE, &src[0][0]);
}

void Shader::sendUniformVec3(const GLchar* name, glm::vec3 src) {
    glUniform3f(glGetUniformLocation(this->programID, name), src.x, src.y, src.z);
}

GLuint Shader::getProgramID(void) {
    return this->programID;
}