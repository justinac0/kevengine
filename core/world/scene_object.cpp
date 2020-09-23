#include "scene_object.hpp"

using namespace kevin;
using namespace kevin::world;

SceneObject::SceneObject(renderer::Transform transform, renderer::Model model) {
    this->m_Transform = transform;
    this->m_Model = model;
}

SceneObject::~SceneObject() {

}

void SceneObject::Update() {
    // NOTE(mitch) i am tired
    this->m_Transform.SetPosition(this->Position);
    this->m_Transform.SetRotation(this->Rotation);
    this->m_Transform.SetScale(this->Scale);

    this->m_Transform.UpdateMatrix();
}

void SceneObject::Render() {
    this->m_Model.DrawElements();
}

Eigen::Matrix4f SceneObject::GetTransformMatrix() {
    return this->m_Transform.GetMatrix();
}

renderer::Model& SceneObject::GetModel() {
    return this->m_Model;
}
