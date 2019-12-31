#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


Model::Model(const char* modelPath, const char* textureParentPath) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath, textureParentPath, 1, 0);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;
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

                vertices.push_back(glm::vec3(attrib.vertices[3*idx.vertex_index+0], attrib.vertices[3*idx.vertex_index+1], attrib.vertices[3*idx.vertex_index+2]));
                normals.push_back(glm::vec3(attrib.normals[3*idx.normal_index+0], attrib.normals[3*idx.normal_index+1], attrib.normals[3*idx.normal_index+2]));
                texcoords.push_back(glm::vec2(attrib.texcoords[2*idx.texcoord_index+0], attrib.texcoords[2*idx.texcoord_index+1]));
                // indices.push_back(idx.vertex_index);

                // Optional: vertex colors
                // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
                // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
                // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
            }

            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }

    this->mesh = new Mesh(vertices, normals, texcoords, indices);

    this->matrix = glm::mat4(1.0f);
}

Model::~Model() {
    this->mesh->~Mesh();
}

void Model::update() {

}

void Model::render() {
    this->mesh->draw();
}

void Model::move(float x, float y, float z) {
    this->position += glm::vec3(x, y, z);
    this->matrix = glm::translate(this->matrix, glm::vec3(x, y, z));
}

void Model::rotate(float x, float y, float z, float angle) {
    this->rotation += glm::vec3(x, y, z);
    this->matrix = glm::rotate(this->matrix, angle, this->rotation);
}

void Model::setScale(float x, float y, float z) {
    this->scale = glm::vec3(x, y, z);
    this->matrix = glm::scale(this->matrix, glm::vec3(x, y, z));
}

glm::mat4 Model::getMatrix() {
    return this->matrix;
}
