#include "scene.hpp"

bool loadVec3Float(std::string line, float* buffer, std::vector<float>* results) {
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

bool loadVec3Int(std::string line, int* buffer, std::vector<int>* results) {
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

bool loadVec2Int(std::string line, int* buffer, std::vector<int>* results) {
    if (sscanf(line.c_str(), "%d %d", buffer, buffer+1) == 2) {
        results->push_back(buffer[0]);
        results->push_back(buffer[1]);
        return true;
    } else {
        std::cerr << "Failed to parse and load Floats correctly." << std::endl;;
        return false;
    }
}

using namespace kevin::world;

Scene::Scene() {

}

Scene::Scene(std::string zoinkFilePath) {
    this->LoadFromZoink(zoinkFilePath);
}

Scene::~Scene() {

}

void Scene::LoadFromZoink(std::string filePath) {
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
                    this->objects.push_back(world::SceneObject(renderer::Transform({ position.at(0), position.at(1), position.at(2) },
                                                                                   { rotation.at(0), rotation.at(1), rotation.at(2) },
                                                                                   { scale.at(0),    scale.at(1),     scale.at(2) }),
                                                               renderer::Model(vertices, normals, colours, indices)));

                    // clear doesn't actually delete data in a vector... i was wrong
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
}