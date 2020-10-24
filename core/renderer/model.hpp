#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <Eigen/Core>
#include "mesh.hpp"
#include "transform.hpp"

namespace kevin {

    namespace renderer {

        class Model : public Mesh {
        public:
            Model();
            Model(std::vector<float> vertices, std::vector<float> normals, std::vector<float> colours, std::vector<int> indices); // inherits Mesh base
            ~Model();
        };

    }
}

#endif // __MODEL_HPP__
