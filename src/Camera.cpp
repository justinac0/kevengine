#include "Camera.h"

Camera::Camera() {
    this->mouseSensitivity  = 0.5f;
    this->speed             = 0.05f;

    this->position  = glm::vec3(0, 0, 30);
    this->forward   = glm::vec3(0, 0, 0);
    this->up        = glm::vec3(0, 1, 0);

    this->yaw   = 3.14f;
    this->pitch = 0.0f;

    this->fov           = 60.0f;
    this->perspective   = glm::perspective(glm::radians(this->fov), (float)4/3, 0.01f, 1000.0f);
    this->view          = glm::mat4(1.0f);
}

Camera::~Camera() {
    
}

void Camera::freeMove() {
    // https://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        this->position += this->forward * this->speed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        this->position -= this->forward * this->speed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        this->position += glm::normalize(glm::cross(this->forward, this->up)) * this->speed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        this->position -= glm::normalize(glm::cross(this->forward, this->up)) * this->speed;
    }

    // Up/Down.
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->position.y += this->speed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        this->position.y -= this->speed;
    }

    float lastX = 400.0f;
    float lastY = 300.0f;

    double xpos, ypos;
    glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
    glfwSetCursorPos(glfwGetCurrentContext(), lastX, lastY);

    float xOffs = xpos - lastX;
    float yOffs = lastY - ypos;
    lastX       = xpos;
    lastY       = ypos;

    xOffs *= this->speed;
    yOffs *= this->speed;

    this->yaw   += xOffs;
    this->pitch += yOffs;

    if (this->pitch > 89.9f) {
        this->pitch = 89.9f;
    }
    if (this->pitch < -89.9f) {
        this->pitch = -89.9f;
    }

    this->forward = glm::normalize(glm::vec3(
        cosf(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
        sinf(glm::radians(this->pitch)),
        sinf(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))
    ));

    this->view = glm::lookAt(this->position, this->position + this->forward, this->up);
}

glm::mat4 Camera::getViewMatrix() {
    return this->view;
}

glm::mat4 Camera::getPerspectiveMatrix() {
    return this->perspective;
}
