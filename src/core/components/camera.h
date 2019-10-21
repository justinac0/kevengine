#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GLFW/glfw3.h>

#include "../utility/math.h"

typedef struct {
    mat4_t matrix;
} camera_t;

camera_t camera_create();
void camera_drag_look(camera_t* camera);

#endif // CAMERA_H
