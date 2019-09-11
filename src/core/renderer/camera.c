#include "camera.h"

camera_t camera_create(void) {
    camera_t camera;

    glm_lookat(
        (vec3){ 0,  0, 3 },
        (vec3){ 0,  0, 0 },
        (vec3){ 0, -1, 0 },
        camera.viewMatrix
    );

    return camera;
}

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
