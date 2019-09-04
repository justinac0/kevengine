#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>

#include "../../lib/cglm/include/cglm/cglm.h"

typedef struct camera_t {
    vec3 position;
    vec3 forward;
    vec3 up;

    mat4 viewMatrix;
} camera_t;

camera_t camera_create(vec3 position, vec3 forward, vec3 up);
void camera_drag(camera_t* camera);

#endif // CAMERA_H
