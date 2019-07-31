#include "camera.h"

camera_t camera_create(vec3 position, vec3 forward, vec3 up) {
    camera_t camera;

    glm_vec3_copy(position, camera.position);
    glm_vec3_copy(forward, camera.forward);
    glm_vec3_copy(up, camera.up);

    glm_lookat(
        (vec3){ 0, 0, 3 },
        (vec3){ 0, 0, 0 },
        (vec3){ 0, 1, 0 },
        camera.viewMatrix
    );

    return camera;
}

void camera_update(camera_t* camera) {

}
