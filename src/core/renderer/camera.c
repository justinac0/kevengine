#include "camera.h"

camera_t camera_create(vec3_t position, vec3_t forward, vec3_t up) {
    camera_t camera;

    camera.position     = position;
    camera.forward      = forward;
    camera.up           = up;

    mat4_identity(&camera.vMatrix);

    return camera;
}

void camera_update(camera_t* camera) {
    mat4_look_at(&camera->vMatrix, camera->position, vec3_add(camera->position, camera->forward), camera->up);
}
