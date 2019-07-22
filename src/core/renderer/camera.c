#include "camera.h"

camera_t camera_create(vec3_t position, vec3_t forward, vec3_t up) {
    camera_t camera;

    camera.position     = position;
    camera.forward      = forward;
    camera.up           = up;

    mat4_identity(&camera.vMatrix);

    return camera;
}

float moveSpeed, yaw, pitch;
void camera_update(camera_t* camera) {
    moveSpeed = 0.25f;

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        camera->position = vec3_add(camera->position, vec3_mul_scalar(camera->forward, moveSpeed));
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        camera->position = vec3_sub(camera->position, vec3_mul_scalar(camera->forward, moveSpeed));
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        camera->position = vec3_add(camera->position, vec3_mul_scalar(vec3_normalize(vec3_cross(camera->forward, camera->up)), moveSpeed));
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        camera->position = vec3_sub(camera->position, vec3_mul_scalar(vec3_normalize(vec3_cross(camera->forward, camera->up)), moveSpeed));
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera->position.y += moveSpeed;
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera->position.y -= moveSpeed;
    }

    float lastX = 800 / 2.0f;
    float lastY = 600 / 2.0f;

    double xpos, ypos;
    glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
    glfwSetCursorPos(glfwGetCurrentContext(), lastX, lastY);

    float xOffs = xpos - lastX;
    float yOffs = lastY - ypos;
    lastX       = xpos;
    lastY       = ypos;

    xOffs *= 0.3f;
    yOffs *= 0.3f;

    yaw   += xOffs;
    pitch += yOffs;

    if (pitch > 89.9f) {
        pitch = 89.9f;
    }
    if (pitch < -89.9f) {
        pitch = -89.9f;
    }

    camera->forward = vec3_normalize((vec3_t) {
        cos(deg_to_rad(yaw)) * cos(deg_to_rad(pitch)),
        sin(deg_to_rad(pitch)),
        sin(deg_to_rad(yaw)) * cos(deg_to_rad(pitch))
    });

    mat4_look_at(&camera->vMatrix, camera->position, vec3_add(camera->position, camera->forward), camera->up);
}
