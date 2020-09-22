#include "model.hpp"

using namespace kevin::renderer;

Model::Model() {
    // default
}

Model::Model(std::vector<float> vertices, std::vector<float> colours, std::vector<int> indices) : Mesh(vertices, colours, indices) {
    this->m_ModelMatrix << 1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1;
}

Model::~Model() {

}

void Model::SetModelMatrix(Eigen::Matrix4f matrix) {
    this->m_ModelMatrix = matrix;
}

Eigen::Matrix4f Model::GetModelMatrix() {
    return this->m_ModelMatrix;
}
