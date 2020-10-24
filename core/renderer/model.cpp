#include "model.hpp"

using namespace kevin::renderer;

Model::Model() {
    // default
}

Model::Model(std::vector<float> vertices, std::vector<float> normals, std::vector<float> colours, std::vector<int> indices) : Mesh(vertices, normals, colours, indices) {}

Model::~Model() {}
