#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include <Eigen/Core>

namespace kevin {

    namespace renderer {

        class Transform {
        private:
            Eigen::Matrix4f m_Matrix;

        public:
            Transform();
            Transform(Eigen::Vector3f position, Eigen::Vector3f rotation, Eigen::Vector3f scale);

            Eigen::Vector3f position;
            Eigen::Vector3f rotation;
            Eigen::Vector3f scale;

            void UpdateMatrix();
            Eigen::Matrix4f GetMatrix();
        };

    }
}

#endif // __TRANSFORM_HPP__
