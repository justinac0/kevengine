#include "model.hpp"

using namespace kevin::renderer;

Model::Model() {
    // default
}

Model::Model(std::vector<float> vertices, std::vector<float> colours, std::vector<int> indices, Transform transform) : Mesh(vertices, colours, indices) {
    this->trasform = transform;
}

Model::~Model() {

}
