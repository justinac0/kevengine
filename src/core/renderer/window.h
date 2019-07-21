#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../math/math.h"
#include "../renderer/ogl.h"

GLFWwindow* window_create(unsigned int width, unsigned int height, const char* title);
void window_destroy(GLFWwindow* window);

void window_update(GLFWwindow* window);

vec2_t window_get_size(GLFWwindow* window);

#endif // WINDOW_H
