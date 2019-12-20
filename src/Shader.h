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
    ~Shader(void);

    void use(void);
    void sendUniformMat4(const GLchar* name, glm::mat4 src);
    void sendUniformVec3(const GLchar* name, glm::vec3 src);
    GLuint getProgramID(void);
};

#endif // SHADER_H
