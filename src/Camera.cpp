#include "Camera.h"

Camera::Camera(float mouseSensitivity, float moveSpeed) {
    this->mouseSensitivity  = mouseSensitivity;
    this->moveSpeed             = moveSpeed;

    this->position  = glm::vec3(0, 100, 0);
    this->forward   = glm::vec3(0, 0, 0);
    this->up        = glm::vec3(0, 1, 0);

    this->yaw   = 3.14f;
    this->pitch = 0.0f;

    this->fov           = 60.0f;
    this->perspective   = glm::perspective(glm::radians(this->fov), (float)4/3, 0.01f, 10000.0f);
    this->view          = glm::mat4(1.0f);
}

Camera::~Camera() {
    
}

double newX, newY;
double oldX, oldY;

void Camera::update() {
    // https://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        this->position += this->forward * this->moveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        this->position -= this->forward * this->moveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        this->position += glm::normalize(glm::cross(this->forward, this->up)) * this->moveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        this->position -= glm::normalize(glm::cross(this->forward, this->up)) * this->moveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        this->position.y -= this->moveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->position.y += this->moveSpeed;
    }

    this->forward = glm::normalize(glm::vec3(
        cosf(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
        sinf(glm::radians(this->pitch)),
        sinf(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))
    ));

    this->view = glm::lookAt(this->position, this->position + this->forward, this->up);

    glfwGetCursorPos(glfwGetCurrentContext(), &newX, &newY);

    if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_1) != GLFW_PRESS) {
        glfwGetCursorPos(glfwGetCurrentContext(), &oldX, &oldY);
        return;
    }

    float xOffs = oldX - newX;
    float yOffs = newY - oldY;

    xOffs *= this->mouseSensitivity * 0.01f;
    yOffs *= this->mouseSensitivity * 0.01f;

    this->yaw   -= xOffs;
    this->pitch -= yOffs;

    if (this->pitch > 89.9f) {
        this->pitch = 89.9f;
    }

    if (this->pitch < -89.9f) {
        this->pitch = -89.9f;
    }
}

glm::mat4 Camera::getViewMatrix(void) {
    return this->view;
}

glm::mat4 Camera::getPerspectiveMatrix(void) {
    return this->perspective;
}

glm::vec3 Camera::getPosition(void) {
    return this->position;
}
