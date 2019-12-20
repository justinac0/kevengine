#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    float mouseSensitivity;
    float speed;

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;

    float yaw;
    float pitch;

    float fov;
    glm::mat4 perspective;
    glm::mat4 view;

public:
    Camera();
    ~Camera();

    void freeMove();

    glm::mat4 getViewMatrix();
    glm::mat4 getPerspectiveMatrix();
};

#endif // CAMERA_H
