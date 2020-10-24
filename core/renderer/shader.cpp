#include "shader.hpp"

namespace util {

    char* ReadFile(std::string filePath) {
        FILE* fileStream = fopen(filePath.c_str(), "r");
        if (!fileStream) {
            return nullptr;
        }

        fseek(fileStream, SEEK_SET, SEEK_END);
        uint32_t length = ftell(fileStream);

        rewind(fileStream);

        char* buffer = (char*) malloc(sizeof(char) * length + 1);

        if (!buffer) {
            return nullptr;
        }
        
        fread(buffer, sizeof(char), length, fileStream);
        fclose(fileStream);

        return buffer;
    }

}

using namespace kevin::renderer;

/* Shader ***************************************************************************/

Shader::Shader(std::string shaderPath, GLenum shaderType) {
    this->m_ID = glCreateShader(shaderType);

    const GLchar* shaderSource = util::ReadFile(shaderPath);
    if (!shaderSource) {
        // failed to read shader file
    }

    glShaderSource(this->m_ID, 1, &shaderSource, 0);
    glCompileShader(this->m_ID);

    GLint isCompiled = 0;
    glGetShaderiv(this->m_ID, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(this->m_ID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(this->m_ID, maxLength, &maxLength, &errorLog[0]);

        std::cout << std::endl;
        std::cout << shaderPath << std::endl;
        for (int i = 0; i < maxLength; i++) {
            std::cout << errorLog[i];
        }

        glDeleteShader(this->m_ID);
    }

}

Shader::~Shader() {
    glDeleteShader(this->m_ID);
}

GLuint Shader::GetID() {
    return this->m_ID;
}

/* ShaderProgram ********************************************************************/

ShaderProgram::ShaderProgram(Shader& vertexShader, Shader& fragmentShader) {
    this->m_ID = glCreateProgram();
    glAttachShader(this->m_ID, vertexShader.GetID());
    glAttachShader(this->m_ID, fragmentShader.GetID());
    glLinkProgram(this->m_ID);

    GLint isLinked = 0;
    glGetProgramiv(this->m_ID, GL_LINK_STATUS, (int*) &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(this->m_ID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(this->m_ID, maxLength, &maxLength, &infoLog[0]);

        std::cout << std::endl;
        std::cout << "shaderprogram: linking error" << std::endl;
        for (int i = 0; i < maxLength; i++) {
            std::cout << infoLog[i];
        }
    
        glDeleteProgram(this->m_ID);
    }

    glDetachShader(this->m_ID, vertexShader.GetID());
    glDetachShader(this->m_ID, fragmentShader.GetID());
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::Use() {
    glUseProgram(this->m_ID);
}

GLuint ShaderProgram::GetID() {
    return this->m_ID;
}
