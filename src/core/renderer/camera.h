#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>

#include "../../deps/cglm/include/cglm/cglm.h"
#include "../util/g_math.h"

typedef struct camera_t {
    vec3 position;
    vec3 forward;
    vec3 up;

    mat4 viewMatrix;
} camera_t;

camera_t camera_create(void);
void camera_drag(camera_t* camera);

#endif // CAMERA_H
