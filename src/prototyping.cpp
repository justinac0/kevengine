#include "prototyping.hpp"

// SCENE /////////////////////////////////////////////
Scene::Scene() {
    identifier = std::string ("TEST");
    root = SceneObject();
}


Scene::Scene(std::string name, SceneObject object) {
    identifier  = name;
    root        = object;
    root.setParent(NULL);
}

Scene::~Scene() {
    
}

void Scene::test() {
    
}

// SCENE OBJECT /////////////////////////////////////////////

SceneObject::SceneObject() {
    this->parent        = NULL;
    this->type          = UNASSIGNED; 
    this->identifier    = std::string ("Undefined");
    this->model         = Model();
}

SceneObject::SceneObject(std::string identifier, std::string modelPath, SceneObjectType type) {
    this->parent        = NULL; 
    this->type          = type;
    this->identifier    = identifier;

    // Model(const char* path, glm::vec3 position, glm::vec3 scale)
    this->model.load(modelPath.c_str());
}

SceneObject::~SceneObject() {

}

SceneObject* SceneObject::Add(SceneObject sceneObject) {
    sceneObject.setParent(this);
    this->children.push_back(sceneObject);
    //return &(*(this->children.end()));
    return NULL;
}

void SceneObject::setParent(SceneObject* sceneObject) {
    this->parent = sceneObject;
}
