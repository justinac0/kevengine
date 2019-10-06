#ifndef WINDOW_H
#define WINDOW_H

#include "../../../deps/glad/glad.h"
#include <GLFW/glfw3.h>

#include "../../math.h"

GLFWwindow* window_create(uint32_t width, uint32_t height, const char* title);
void window_update(GLFWwindow* pWindow);
void window_destroy(GLFWwindow* pWindow);

vec2_t window_get_size(GLFWwindow* pWindow);

#endif // WINDOW_H
