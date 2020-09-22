#include "transform.hpp"

using namespace kevin::renderer;

Transform::Transform() {
    // default
}

Transform::Transform(Eigen::Vector3f position, Eigen::Vector3f scale, Eigen::Vector3f rotation) {
    this->m_Position = position;
    this->m_Scale = scale;
    this->m_Rotation = rotation;
    this->UpdateMatrix();
}

void Transform::SetPosition(Eigen::Vector3f newPosition) {
    this->m_Position = newPosition;
}

Eigen::Vector3f Transform::GetPosition() {
    return this->m_Position;
}

void Transform::SetScale(Eigen::Vector3f newScale) {
    this->m_Scale = newScale;
}

Eigen::Vector3f Transform::GetScale() {
    return this->m_Scale;
}

void Transform::SetRotation(Eigen::Vector3f newRotation) {
    this->m_Rotation = newRotation;
}

Eigen::Vector3f Transform::GetRotation() {
    return this->m_Rotation;
}

void Transform::UpdateMatrix() {
    Eigen::Matrix4f newTransform;
    newTransform << 1, 0, 0, this->m_Position(0),
                    0, 1, 0, this->m_Position(1),
                    0, 0, 1, this->m_Position(2),
                    0, 0, 0, 1;

    Eigen::Matrix4f newScale;
    newScale << this->m_Scale(0), 0, 0, 0,
                0, this->m_Scale(1), 0, 0,
                0, 0, this->m_Scale(2), 0,
                0, 0, 0, 1;

    Eigen::Matrix4f rotationX;
    rotationX << 1, 0, 0, 0,
                    0, cosf(this->m_Rotation(0)), -sinf(this->m_Rotation(0)), 0,
                    0, sinf(this->m_Rotation(0)), cosf(this->m_Rotation(0)),  0,
                    0, 0, 0, 1;

    Eigen::Matrix4f rotationY;
    rotationY << cosf(this->m_Rotation(1)),  0, sinf(this->m_Rotation(1)), 0,
                    0, 1, 0, 0,
                    -sinf(this->m_Rotation(1)), 0, cosf(this->m_Rotation(1)), 0,
                    0, 0, 0, 1;

    Eigen::Matrix4f rotationZ;
    rotationZ << cosf(this->m_Rotation(2)), -sinf(this->m_Rotation(2)), 0, 0,
                    sinf(this->m_Rotation(2)), cosf(this->m_Rotation(2)),  0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1;

    Eigen::Matrix4f newRotation = rotationX * rotationY * rotationZ;

    this->m_Matrix = (newTransform * newScale * newRotation);
}

Eigen::Matrix4f Transform::GetMatrix() {
    return this->m_Matrix;
}
