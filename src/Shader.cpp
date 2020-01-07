#include "Shader.h"

char* readFile(const char* path) {
    FILE* fileStream = NULL;
    if ((fileStream = fopen(path, "r")) == NULL) {
        printf("Failed to open file at location: %s\n", path);
        exit(EXIT_FAILURE);
    }

    fseek(fileStream, 0, SEEK_END);
    uint32_t fileLength = ftell(fileStream);
    rewind(fileStream);

    char* buffer = NULL;
    if ((buffer = (char*)calloc(fileLength + 1, sizeof(char))) == NULL) {
        printf("Cannot allocate memory for file buffer\n");
        exit(EXIT_FAILURE);
    }

    fread(buffer, sizeof(char), fileLength, fileStream);

    fclose(fileStream);

    return buffer;
}

///////////////////////////////////////////////////////////////////

Shader::Shader(void) {

}

Shader::~Shader(void) {
    glDeleteProgram(this->programID);
}

void Shader::load(const char* vertexShaderPath, const char* fragmentShaderPath) {
    char* vertexSource = readFile(vertexShaderPath);
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

    char* fragmentSource = readFile(fragmentShaderPath);
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