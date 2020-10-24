#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <iostream>
#include <vector>

#include <fstream>
#include <string>

#include "scene_object.hpp"

namespace kevin {

    namespace world {

        class Scene {
        public:
            Scene();
            Scene(std::string zoinkFilePath);
            ~Scene();

            void LoadFromZoink(std::string filePath);

            std::vector<SceneObject> objects;

        };

    }
}
#endif // __SCENE_HPP__
