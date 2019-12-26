#include "Shader.h"

char* readFile(const char* path) {
    FILE* fileStream = fopen(path, "r");
    if (!fileStream) {}
    fseek(fileStream, 0, SEEK_END);

    uint32_t length = ftell(fileStream);
    rewind(fileStream);
    char* buffer = (char*) malloc(length);
    fread(buffer, sizeof(char), length, fileStream);

    fclose(fileStream);

    return buffer; 
}
Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    const char* vertexSource = readFile(vertexShaderPath);
    GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexSource, NULL);
    glCompileShader(vertexID);

    GLint success = 0;
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vertexID, maxLength, &maxLength, &errorLog[0]);

        std::cout << vertexShaderPath << std::endl;
        for (int i = 0; i < maxLength; i++) {
            std::cout << errorLog[i];
        }
    }

    std::cout << std::endl;

    const char* fragmentSource = readFile(fragmentShaderPath);
    GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentSource, NULL);
    glCompileShader(fragmentID);

    success = 0;
    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fragmentID, maxLength, &maxLength, &errorLog[0]);

        std::cout << fragmentShaderPath << std::endl;
        for (int i = 0; i < maxLength; i++) {
            std::cout << errorLog[i];
        }
    }

    this->programID = glCreateProgram();
    glAttachShader(this->programID, vertexID);
    glAttachShader(this->programID, fragmentID);
    glLinkProgram(this->programID);
    glUseProgram(this->programID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
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