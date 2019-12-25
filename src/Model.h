#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"

class Model {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 matrix;
    Mesh* mesh;

public:
    Model(const char* path);
    ~Model();

    void render();
    void move(float x, float y, float z);
    void rotate(float x, float y, float z, float angle);
    void setScale(float x, float y, float z);

    glm::mat4 getMatrix();
};

#endif // MODEL_H
