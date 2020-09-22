#include "camera.hpp"

using namespace kevin::world;

inline Eigen::Matrix4f _CreateProjectionMatrix(float fov, float aspect, float znear, float zfar) {
    float range = atan(fov / 2.0f) * znear;
    float sx    = (2.0f * znear) / (range * aspect + range * aspect);
    float sy    = znear / range;
    float sz    = -(zfar + znear) / (zfar - znear);
    float pz    = -(2.0f * zfar * znear) / (zfar - znear);

    Eigen::Matrix4f perspective;
    perspective << sx,    0.0f,  0.0f, 0.0f,
                   0.0f,  sy,    0.0f, 0.0f,
                   0.0f,  0.0f,  sz,   pz,
                   0.0f,  0.0f, -1.0f, 0.0f;

    return perspective;
}

Camera::Camera(float mouseSensitivity, float moveSpeed) {
    this->m_MouseSensitivity = mouseSensitivity;
    this->m_MoveSpeed        = moveSpeed;

    this->m_Position = { 0.0f, 0.0f, 0.0f };
    this->m_Forward  = { 0.0f, 0.0f, 1.0f };
    this->m_Up       = { 0.0f, 1.0f, 0.0f };

    this->m_Yaw   = M_PI;
    this->m_Pitch = 0.0f;

    this->m_Fov = 75.0f;
    this->m_ProjectionMatrix = _CreateProjectionMatrix((M_PI / 180.0f) * this->m_Fov, (float)16.0f / 9.0f, 0.01f, 1000.0f);

    this->m_ViewMatrix << 1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1;
    this->m_ViewMatrix.transposeInPlace();
}

Camera::~Camera() {

}

void Camera::Update() {
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        this->m_Position += this->m_Forward * this->m_MoveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        this->m_Position -= this->m_Forward * this->m_MoveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        this->m_Position -= Eigen::Vector3f{ 1, 0, 0 } * this->m_MoveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        this->m_Position += Eigen::Vector3f{ 1, 0, 0 } * this->m_MoveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->m_Position -= this->m_Up * this->m_MoveSpeed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        this->m_Position += this->m_Up * this->m_MoveSpeed;
    }

    this->m_ViewMatrix << 1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          this->m_Position(0), this->m_Position(1), this->m_Position(2), 1;
    this->m_ViewMatrix.transposeInPlace();
}

Eigen::Vector3f Camera::GetPosition() {
    return this->m_Position;
}

Eigen::Matrix4f Camera::GetViewMatrix() {
    return this->m_ViewMatrix;
}

Eigen::Matrix4f Camera::GetProjectionMatrix() {
    return this->m_ProjectionMatrix;
}
