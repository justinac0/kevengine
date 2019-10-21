#include "camera.h"

camera_t camera_create() {
    camera_t camera;

    camera.matrix = m_mat4_identity();

    return camera;
}

void camera_drag_look(camera_t* camera) {

}