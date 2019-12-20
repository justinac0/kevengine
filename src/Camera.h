#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    float mouseSensitivity;
    float moveSpeed;

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;

    float yaw;
    float pitch;

    float fov;
    glm::mat4 perspective;
    glm::mat4 view;

public:
    Camera(float mouseSensitivity, float moveSpeed);
    ~Camera();

    void freeMove();

    glm::mat4 getViewMatrix(void);
    glm::mat4 getPerspectiveMatrix(void);
    glm::vec3 getPosition(void);
};

#endif // CAMERA_H
