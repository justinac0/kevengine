#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader {
private:
    GLuint vertexShaderID;
    GLuint fragmentShaderID;
    GLuint programID;

public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();

    void use();
    void sendUniformMat4(const GLchar* name, glm::mat4 src);
    GLuint getProgramID();
};

#endif // SHADER_H
