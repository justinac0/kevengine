#include "transform.hpp"

using namespace kevin::renderer;

Transform::Transform() {
    this->m_Matrix << 1,0,0,0,
                      0,1,0,0,
                      0,0,1,0,
                      0,0,0,1;
}

Transform::Transform(Eigen::Vector3f position, Eigen::Vector3f rotation, Eigen::Vector3f scale) {
    this->m_Matrix << 1,0,0,0,
                      0,1,0,0,
                      0,0,1,0,
                      0,0,0,1;

    this->position = position;
    this->rotation = rotation;
    this->scale    = scale;

    this->UpdateMatrix();
}

void Transform::UpdateMatrix() {
    Eigen::Matrix4f newTransform;
    newTransform << 1, 0, 0, this->position(0),
                    0, 1, 0, this->position(1),
                    0, 0, 1, this->position(2),
                    0, 0, 0, 1;

    Eigen::Matrix4f newScale;
    newScale << this->scale(0), 0, 0, 0,
                0, this->scale(1), 0, 0,
                0, 0, this->scale(2), 0,
                0, 0, 0, 1;

    Eigen::Matrix4f rotationX;
    rotationX << 1, 0, 0, 0,
                 0, cosf(this->rotation(0)), -sinf(this->rotation(0)), 0,
                 0, sinf(this->rotation(0)), cosf(this->rotation(0)),  0,
                 0, 0, 0, 1;

    Eigen::Matrix4f rotationY;
    rotationY << cosf(this->rotation(1)),  0, sinf(this->rotation(1)), 0,
                 0, 1, 0, 0,
                -sinf(this->rotation(1)), 0, cosf(this->rotation(1)), 0,
                 0, 0, 0, 1;

    Eigen::Matrix4f rotationZ;
    rotationZ << cosf(this->rotation(2)), -sinf(this->rotation(2)), 0, 0,
                 sinf(this->rotation(2)), cosf(this->rotation(2)),  0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1;

    Eigen::Matrix4f newRotation = rotationX * rotationY * rotationZ;

    this->m_Matrix = (newTransform * newScale * newRotation);
}

Eigen::Matrix4f Transform::GetMatrix() {
    return this->m_Matrix;
}
