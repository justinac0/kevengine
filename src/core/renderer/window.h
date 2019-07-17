#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include "../deps/glad/glad.h"
#include <GLFW/glfw3.h>

#include "../math/math.h"

GLFWwindow* window_create(unsigned int width, unsigned int height, const char* title);
void window_destroy(GLFWwindow* window);

void window_update(GLFWwindow* window);

int window_get_request_close(GLFWwindow* window);
vec2_t window_get_size(GLFWwindow* window);

#endif // WINDOW_H
