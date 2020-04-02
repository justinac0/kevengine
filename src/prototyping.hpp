#ifndef PROTOTYPING_HPP_
#define PROTOTYPING_HPP_

#include <iostream> // For testing
#include <vector>
#include <string>

#include "scene/Model.hpp"
#include "scene/Camera.hpp"

typedef enum {
    MODEL,
    CAMERA,
    UNASSIGNED    
} SceneObjectType;

class SceneObject {
    private:
        // Relational Data
        std::vector<SceneObject> children;
        SceneObject *parent;

        // 
        SceneObjectType type; 
        std::string identifier;
        Model model;

    public:
        SceneObject(); // DUMMY
        SceneObject(std::string identifier, std::string modelPath, SceneObjectType type);
        ~SceneObject(void);

        SceneObject* Add(SceneObject sceneObject);
        void setParent(SceneObject *sceneObject);
};

class Scene {
    private:
        std::string identifier;

    public:
        SceneObject root;

    public:
        Scene();

        Scene(std::string name, SceneObject object);
        ~Scene(void);

        void test();

};

#endif // PROTOTYPING_HPP_
