#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include "../math/math.h"

typedef struct camera_t {
    vec3_t position;
    vec3_t forward;
    vec3_t up;

    mat4_t vMatrix;
} camera_t;

camera_t camera_create(vec3_t position, vec3_t forward, vec3_t up);
void camera_update(camera_t* camera);

#endif // CAMERA_H
