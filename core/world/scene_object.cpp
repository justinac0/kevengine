#include "scene_object.hpp"

using namespace kevin;
using namespace kevin::world;

SceneObject::SceneObject(renderer::Transform transform, renderer::Model model) {
    this->m_Transform = transform;
    this->m_Model = model;
}

SceneObject::~SceneObject() {

}

void SceneObject::Move(float x, float y, float z) {
    this->m_Transform.position = { x, y, z };
    this->UpdateModel();
}

void SceneObject::Rotate(float x, float y, float z) {
    this->m_Transform.rotation = { x, y, z };
    this->UpdateModel();
}

void SceneObject::Scale(float x, float y, float z) {
    this->m_Transform.scale = { x, y, z };
    this->UpdateModel();
}

void SceneObject::UpdateModel() {
    this->m_Transform.UpdateMatrix();
}

void SceneObject::RenderModel() {
    this->m_Model.DrawElements();
}

renderer::Model SceneObject::GetModel() {
    return this->m_Model;
}

renderer::Transform SceneObject::GetTransform() {
    return this->m_Transform;
}
