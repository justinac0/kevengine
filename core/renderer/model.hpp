#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <Eigen/Core>
#include "mesh.hpp"

namespace kevin {

    namespace renderer {

        class Model : public Mesh {
        public:
            Model();
            Model(std::vector<float> vertices, std::vector<float> colours, std::vector<int> indices); // inherits Mesh base
            ~Model();

            void SetModelMatrix(Eigen::Matrix4f matrix);
            Eigen::Matrix4f GetModelMatrix();

        private:
            Eigen::Matrix4f m_ModelMatrix;
        };

    }
}

#endif // __MODEL_HPP__
