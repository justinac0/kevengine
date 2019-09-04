#include "camera.h"

static mat4 matRoll, matPitch, matYaw;
static mat4 rotate, translate;

static float roll, pitch, yaw;

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

// https://www.3dgep.com/understanding-the-view-matrix/

static double oldX, oldY;
static double newX, newY;

void camera_drag(camera_t* camera) {

    {
        if (!glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
            glfwGetCursorPos(glfwGetCurrentContext(), &oldX, &oldY);
            return;
        }

        uint32_t windowWidth, windowHeight;
        glfwGetWindowSize(glfwGetCurrentContext(), &windowWidth, &windowHeight);

        glfwGetCursorPos(glfwGetCurrentContext(), &newX, &newY);

        if (newX > windowWidth || newX < 0 || newY > windowHeight || newY < 0) {
            return;
        } else {
            glfwGetCursorPos(glfwGetCurrentContext(), &oldX, &oldY);
        }
    }
}
