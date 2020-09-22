#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <iostream>
#include <vector>

#include <cstdlib>

#include <glad/glad.h>

namespace kevin {

    namespace renderer {

        class Shader {
        public:
            Shader(std::string shaderPath, GLenum shaderType);
            ~Shader();

            GLuint GetID();
        private:
            GLuint m_ID;
        };

        class ShaderProgram {
        public:
            ShaderProgram(Shader& vertexShader, Shader& fragmentShader);
            ~ShaderProgram();

            void Use();
            GLuint GetID();
        private:
            GLuint m_ID;
        };

    }
}

#endif // __SHADER_HPP__
