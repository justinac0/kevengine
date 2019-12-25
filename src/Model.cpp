#include "Model.h"

Model::Model(const char* path) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoords;
    std::vector<GLuint> indices;

    FILE* fileStream = nullptr;

    if ((fileStream = fopen(path, "r")) == nullptr) {
        std::cout << stderr << "Can't open file stream: " << std::endl;
        return;
    }

    GLfloat v0, v1, v2;
    GLfloat n0, n1, n2;
    GLfloat t0, t1;
    GLuint  f0, f1, f2, f3, f4, f5, f6, f7, f8;

    char lineBuffer[512];
    while (fgets(lineBuffer, 512, fileStream)) {
        if (sscanf(lineBuffer, "v %f %f %f", &v0, &v1, &v2) == 3) {
            vertices.push_back(glm::vec3(v0, v1, v2));
        }

        if (sscanf(lineBuffer, "vt %f %f", &t0, &t1) == 2) {
            textureCoords.push_back(glm::vec2(t0, t1));
        }

        if (sscanf(lineBuffer, "f %d/%d %d/%d", &f0, &f1, &f2, &f3) == 4) {
            indices.push_back(f0-1);
            indices.push_back(f2-1);
        }

        if (sscanf(lineBuffer, "f %d//%d %d//%d %d//%d", &f0, &f1, &f2, &f3, &f4, &f5) == 6) {
            indices.push_back(f0-1);
            indices.push_back(f2-1);
            indices.push_back(f4-1);
        }

        if (sscanf(lineBuffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f0, &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8) == 9) {
            indices.push_back(f0-1);
            indices.push_back(f3-1);
            indices.push_back(f6-1);
        }
    }

    fclose(fileStream);

    normals.resize(indices.size());

    // Begin Function CalculateSurfaceNormal (Input Polygon) Returns Vector

    // Set Vertex Normal to (0, 0, 0)

    // Begin Cycle for Index in [0, Polygon.vertexNumber)

    //     Set Vertex Current to Polygon.verts[Index]
    //     Set Vertex Next    to Polygon.verts[(Index plus 1) mod Polygon.vertexNumber]

    //     Set Normal.x to Sum of Normal.x and (multiply (Current.y minus Next.y) by (Current.z plus Next.z))
    //     Set Normal.y to Sum of Normal.y and (multiply (Current.z minus Next.z) by (Current.x plus Next.x))
    //     Set Normal.z to Sum of Normal.z and (multiply (Current.x minus Next.x) by (Current.y plus Next.y))

    // End Cycle

    // Returning Normalize(Normal)

    // End Function

    // calculate normals: https://github.com/BennyQBD/ModernOpenGLTutorial
    for(unsigned int i = 0; i < indices.size(); i += 3) {
        int i0 = indices[i];
        int i1 = indices[i + 1];
        int i2 = indices[i + 2];

        glm::vec3 v1 = vertices[i1] - vertices[i0];
        glm::vec3 v2 = vertices[i2] - vertices[i0];
        
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
            
        normals[i0] += normal;
        normals[i1] += normal;
        normals[i2] += normal;
    }

    for(unsigned int i = 0; i < vertices.size(); i++) {
        normals[i] = glm::normalize(normals[i]);
    }

    this->mesh = new Mesh(vertices, normals, textureCoords, indices);

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
    this->matrix = glm::translate(this->matrix, this->position);
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
