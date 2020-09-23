#include "kevin.hpp"

#include <Eigen/Core>

using namespace kevin;

const uint32_t WINDOW_WIDTH  = 1280;
const uint32_t WINDOW_HEIGHT = 720;

std::vector<float> vertices = {
    -1, -1, 0,
     1, -1, 0,
     0,  1, 0
};

std::vector<float> colours = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0
};

std::vector<int> indices = {
    0, 1, 2
};

// remove later nerd
inline Eigen::Matrix4f ProjectionMatrix(float fov, float aspect, float znear, float zfar) {
    float range = atan(fov / 2.0f) * znear;
    float sx    = (2.0f * znear) / (range * aspect + range * aspect);
    float sy    = znear / range;
    float sz    = -(zfar + znear) / (zfar - znear);
    float pz    = -(2.0f * zfar * znear) / (zfar - znear);

    Eigen::Matrix4f perspective;
    perspective << sx,    0.0f,  0.0f, 0.0f,
                   0.0f,  sy,    0.0f, 0.0f,
                   0.0f,  0.0f,  sz,   pz,
                   0.0f,  0.0f, -1.0f, 0.0f;

    return perspective;
}

// NOTE : TEMPORARRRRYYYYYY >>>> TIME TO MOVE THIS TO SCENE
// i dont like the fact that i have to pass in the ubo directly .... (uniform buffers)
// scene objects should get the projection and view from some scene class or camera
void SceneRender(std::vector<renderer::Model>* pScene, renderer::ShaderProgram shaderProgram, world::Camera& camera) {
    if (!pScene) {
        // throw error
        return;
    }
    for (size_t i = 0; i < pScene->size(); i++) {
        shaderProgram.Use();

        Eigen::Matrix4f model;
        model << 1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f;

        camera.Update();

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "m_projection"), 1, GL_FALSE, &camera.GetProjectionMatrix()(0));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "m_view"), 1, GL_FALSE, &camera.GetViewMatrix()(0));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "m_transform"), 1, GL_FALSE, &(*pScene)[i].trasform.GetMatrix()(0));

        (*pScene)[i].DrawElements();
    }
}


// NOTE (mitch)
// you need to do error checking on values passed by pointers because
// nullptr values can be passed in and cause segfaults..
// or you could just pass by reference.
//
// also if the function is going to load in a vec3 make sure it uses the correct
// vec3 format 'Eigen::Vector3f' ('Eigen::Vector3i' for the vec3Int function) <3
//
inline bool loadVec3Float(std::string line, float* buffer, std::vector<float>* results) {
    if (sscanf(line.c_str(), "%f %f %f", buffer, buffer+1, buffer+2) == 3) {
        results->push_back(buffer[0]);
        results->push_back(buffer[1]);
        results->push_back(buffer[2]);
        return true;
    } else {
        std::cerr << "Failed to parse and load Ints correctly." << std::endl;;
        return false;
    }
}

inline bool loadVec3Int(std::string line, int* buffer, std::vector<int>* results) {
    if (sscanf(line.c_str(), "%d %d %d", buffer, buffer+1, buffer+2) == 3) {
        results->push_back(buffer[0]);
        results->push_back(buffer[1]);
        results->push_back(buffer[2]);
        return true;
    } else {
        std::cerr << "Failed to parse and load Floats correctly." << std::endl;;
        return false;
    }
}

inline bool loadVec2Int(std::string line, int* buffer, std::vector<int>* results) {
    if (sscanf(line.c_str(), "%d %d", buffer, buffer+1) == 2) {
        results->push_back(buffer[0]);
        results->push_back(buffer[1]);
        return true;
    } else {
        std::cerr << "Failed to parse and load Floats correctly." << std::endl;;
        return false;
    }
}

#include <iostream>
#include <fstream>
#include <string>

std::vector<renderer::Model> loadModelFromFile(const char* filePath) {
    std::vector<renderer::Model> models = {};
    float floatBuf[3];
    int intBuf[3];
    char charBuf[256];

    enum Region { NONE = -1, VERTICES, NORMALS, COLOURS, INDICES, POSITION, SCALE, ROTATION };
    Region curr = NONE;

    std::vector<float> vertices = {};
    std::vector<float> normals  = {};
    std::vector<float> colours  = {};
    std::vector<int>   indices  = {};

    std::vector<float> position = {};
    std::vector<float> scale    = {};
    std::vector<float> rotation = {};

    std::cout << "Loading model from file: " << filePath << std::endl;

    std::string buffer;
    std::ifstream myfile (filePath);
    if (myfile.is_open()) {
        while (std::getline(myfile, buffer)) {
            if (buffer.length() == 0) {
                continue;
            }

            if (buffer[0] == ';') {
                if (sscanf(buffer.c_str(), "; model %255s", charBuf) == 1) {
                    models.push_back(renderer::Model(vertices, normals, indices, renderer::Transform({ position.at(0), position.at(1), position.at(2) },
                                                                                                     { scale.at(0), scale.at(1), scale.at(2) },
                                                                                                     { rotation.at(0), rotation.at(1), rotation.at(2) })));
                    vertices.clear();
                    normals.clear();
                    colours.clear();
                    indices.clear();

                    position.clear();
                    scale.clear();
                    rotation.clear();

                    curr = NONE;
                    std::cout << "Loaded Model: " << charBuf << std::endl;
                } else if (sscanf(buffer.c_str(), "; %255s", charBuf) == 1) {
                    // std::cout << "Region: " << charBuf << std::endl;
                    if (strcmp(charBuf, "vertices") == 0) // be consistent with {} plox
                        curr = VERTICES;
                    else if (strcmp(charBuf, "normals") == 0)
                        curr = NORMALS;
                    else if (strcmp(charBuf, "colours") == 0)
                        curr = COLOURS;
                    else if (strcmp(charBuf, "indices") == 0)
                        curr = INDICES;
                    else if (strcmp(charBuf, "position") == 0)
                        curr = POSITION;
                    else if (strcmp(charBuf, "scale") == 0)
                        curr = SCALE;
                    else if (strcmp(charBuf, "rotation") == 0)
                        curr = ROTATION;
                    else
                        std::cerr << "I want to die right now." << std::endl;
                } else {
                    std::cerr << "Something went wrong while parsing file." << std::endl;
                }
            } else {
                switch (curr) {
                    case VERTICES:
                        if (loadVec3Float(buffer, floatBuf, &vertices)) {
                            // std::cout << "Vertex:\t" << floatBuf[0] << ", " << floatBuf[1] << ", " << floatBuf[2] << std::endl;
                        }
                        break;
                    case NORMALS:
                        if (loadVec3Float(buffer, floatBuf, &normals)) {
                            // std::cout << "Normal:\t" << floatBuf[0] << ", " << floatBuf[1] << ", " <<  floatBuf[2] << std::endl;
                        }
                        break;
                    case COLOURS:
                        if (loadVec3Float(buffer, floatBuf, &colours)) {
                            // std::cout << "Colour:\t" << floatBuf[0] << ", " << floatBuf[1] << ", " << floatBuf[2] << std::endl;
                        }
                        break;
                    case INDICES:
                        if (loadVec3Int(buffer, intBuf, &indices)) {
                            // std::cout << "Index:\t" << intBuf[0] << ", " << intBuf[1] << ", " << intBuf[2] << std::endl;
                        }
                        break;
                    case POSITION:
                        if (loadVec3Float(buffer, floatBuf, &position)) {
                            // std::cout << "Index:\t" << intBuf[0] << ", " << intBuf[1] << ", " << intBuf[2] << std::endl;
                        }
                        break;

                    case SCALE:
                        if (loadVec3Float(buffer, floatBuf, &scale)) {
                            // std::cout << "Index:\t" << intBuf[0] << ", " << intBuf[1] << ", " << intBuf[2] << std::endl;
                        }
                        break;

                    case ROTATION:
                        if (loadVec3Float(buffer, floatBuf, &rotation)) {
                            // std::cout << "Index:\t" << intBuf[0] << ", " << intBuf[1] << ", " << intBuf[2] << std::endl;
                        }
                        break;
                    default: //err
                        break;
                }

                // std::cerr << "Something went wrong while parsing file." << std::endl;
            }
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file: " << filePath << std::endl; 
    }

    return models;
}

int main() {
    renderer::Renderer renderer = renderer::Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    renderer::Shader vertexShader = renderer::Shader("build/vertex.glsl", GL_VERTEX_SHADER);
    renderer::Shader fragmentShader = renderer::Shader("build/fragment.glsl", GL_FRAGMENT_SHADER);
    renderer::ShaderProgram shaderProgram = renderer::ShaderProgram(vertexShader, fragmentShader);

    world::Camera camera(1.0f, 0.05f);
    // world::SceneObject triangle(renderer::Transform({ 0, 0, -10 }, { 1, 1, 1 }, { 0, 0, 0 }), renderer::Model(vertices, colours, indices));

    std::vector<renderer::Model> scene = loadModelFromFile("./build/file.znk");

    while (!renderer.GetWindowShouldClose()) {
        renderer.UpdateWindow();

        camera.Update();

        // shaderProgram.Use();

        // triangle.Position = { 0, 0, -10 };
        // triangle.Scale = { 1, 1, 1 };
        // triangle.Rotation = { 0, 0, 0 };

        // triangle.Update();
        // triangle.Render();

        // glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "m_projection"), 1, GL_FALSE, &camera.GetProjectionMatrix()(0));
        // glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "m_view"), 1, GL_FALSE, &camera.GetViewMatrix()(0));
        // glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetID(), "m_transform"), 1, GL_FALSE, &triangle.GetTransformMatrix()(0));

        SceneRender(&scene, shaderProgram, camera);
    }

    return 0;
}
