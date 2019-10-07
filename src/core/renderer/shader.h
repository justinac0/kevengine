#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../deps/glad/glad.h"

#include "../utility/util.h"

// compile individual shader source.
GLuint shader_compile(const char* fileLocation, const int shaderType);
// loads in default built-in shaders.
GLuint shader_load_default(void);
// load in vertex and fragment shaders and return shader program ID.
GLuint shader_load(const char* vsFileLocation, const char* fsFileLocation);
// use given shader.
void shader_use(GLuint programID);

#endif // SHADER_H
