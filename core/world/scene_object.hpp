#ifndef __SCENE_OBJECT_HPP__
#define __SCENE_OBJECT_HPP__

#include <Eigen/Core>
#include "../renderer/model.hpp"
#include "../renderer/transform.hpp"

namespace kevin {

    namespace world {

        class SceneObject {
        public:
            Eigen::Vector3f Position;
            Eigen::Vector3f Scale;
            Eigen::Vector3f Rotation;

        public:
            SceneObject(renderer::Transform transform, renderer::Model model);
            ~SceneObject();

            void Update();
            void Render();

            Eigen::Matrix4f GetTransformMatrix();
            renderer::Model& GetModel();

        private:
            renderer::Transform m_Transform;
            renderer::Model m_Model;
        };

    };

};

#endif // __SCENE_OBJECT_HPP__