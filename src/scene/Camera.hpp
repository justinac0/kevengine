#ifndef CAMERA_HPP_
#define CAMERA_HPP_

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
    Camera();
    ~Camera();

    // include default position and rotations would be nice
    void init(float mouseSensitivity, float moveSpeed);
    void update(GLFWwindow* window);

    glm::vec3 getPosition(void);

    glm::mat4 getViewMatrix(void);
    glm::mat4 getPerspectiveMatrix(void);
};

#endif // CAMERA_HPP_
