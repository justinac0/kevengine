#include "Model.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Model::Model() {
}

// Model::Model(const char* path, glm::vec3 position, glm::vec3 scale) {
//     this->position  = position;
//     this->scale     = scale;

//     this->matrix = glm::mat4(1.0f);
//     this->move(position.x, position.y, position.z);
//     this->setScale(scale.x, scale.y, scale.z);

//     this->load(path);
// }

void Model::load(const char* path) {
    // it would be nice to move the loading to a load manager
    // or something for when we import more than just wavefront
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path, NULL, 1, 0);

    std::vector<tinyobj::real_t> primitiveData;
    std::vector<glm::vec3> normals;
    // std::vector<glm::vec2> texcoords;
    std::vector<glm::vec3> colors;
    std::vector<GLuint> indices;

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    materials.push_back(tinyobj::material_t());

    for (size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            for (size_t v = 0; v < (long unsigned int)fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                // verts
                primitiveData.push_back(attrib.vertices[3*idx.vertex_index+0]);
                primitiveData.push_back(attrib.vertices[3*idx.vertex_index+1]);
                primitiveData.push_back(attrib.vertices[3*idx.vertex_index+2]);

                // colors
                if (vy > 300.0) {
                    primitiveData.push_back(1);
                    primitiveData.push_back(1);
                    primitiveData.push_back(1);
                } else if (vy > 200.0) {
                    primitiveData.push_back(0.7);
                    primitiveData.push_back(0.7);
                    primitiveData.push_back(0.7);
                } else if (vy > 100.0) {
                    primitiveData.push_back(0.5);
                    primitiveData.push_back(0.5);
                    primitiveData.push_back(0.5);
                } else if (vy > 50.0) {
                    primitiveData.push_back(0.3);
                    primitiveData.push_back(0.3);
                    primitiveData.push_back(0.3);
                } else {
                    primitiveData.push_back(0.2);
                    primitiveData.push_back(0.2);
                    primitiveData.push_back(0.2);
                }

                normals.push_back(glm::vec3(attrib.normals[3*idx.normal_index+0], attrib.normals[3*idx.normal_index+1], attrib.normals[3*idx.normal_index+2]));
                // texcoords.push_back(glm::vec2(attrib.texcoords[2*idx.texcoord_index+0], attrib.texcoords[2*idx.texcoord_index+1]));
                // indices.push_back(idx.vertex_index);
            }

            index_offset += fv;

            shapes[s].mesh.material_ids[f];
        }
    }

    this->mesh = new Mesh(primitiveData, normals, indices);

    this->matrix = glm::mat4(1.0f);
}

Model::~Model() {
    this->mesh->~Mesh();
}

void Model::render() {
    this->mesh->draw();
}

void Model::move(float x, float y, float z) {
    this->position += glm::vec3(x, y, z);
    this->matrix = glm::translate(this->matrix, glm::vec3(x, y, z));
}

void Model::setScale(float x, float y, float z) {
    this->scale = glm::vec3(x, y, z);
    this->matrix = glm::scale(this->matrix, glm::vec3(x, y, z));
}

glm::mat4 Model::getMatrix() {
    return this->matrix;
}

glm::vec3 Model::getPosition() {
    return this->position;
}
