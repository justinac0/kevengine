#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../render/Mesh.hpp"

class Model {
private:
    glm::vec3 position;
    glm::vec3 scale;

    glm::mat4 matrix;

    Mesh* mesh;

public:
    Model(void);
    // Model(const char* path, glm::vec3 position, glm::vec3 scale);
    ~Model(void);

    void render();
    void load(const char* path);
    void move(float x, float y, float z);
    void setScale(float x, float y, float z);

    glm::mat4 getMatrix();
    glm::vec3 getPosition();
};

#endif // MODEL_HPP_
