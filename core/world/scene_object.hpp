#ifndef __SCENE_OBJECT_HPP__
#define __SCENE_OBJECT_HPP__

#include <Eigen/Core>
#include "../renderer/model.hpp"
#include "../renderer/transform.hpp"

namespace kevin {

    namespace world {

        class SceneObject {
        public:
            SceneObject(renderer::Transform transform, renderer::Model model);
            ~SceneObject();

            void Move(float x, float y, float z);
            void Rotate(float x, float y, float z);
            void Scale(float x, float y, float z);

            void UpdateModel();
            void RenderModel();

            renderer::Model GetModel();
            renderer::Transform GetTransform();

        private:
            renderer::Model m_Model;
            renderer::Transform m_Transform;
        };

    };

};

#endif // __SCENE_OBJECT_HPP__