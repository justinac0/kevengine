#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include <Eigen/Core>

namespace kevin {

    namespace renderer {

        class Transform {
        private:
            Eigen::Vector3f m_Position;
            Eigen::Vector3f m_Scale;

            // NOTE(justin, mitch)
            //  Generating our matrix rotation from this like this
            //  is terribly inefficient, mainly because 3 matricies
            //  are created to generate the final rotation matrix.
            Eigen::Vector3f m_Rotation;

            Eigen::Matrix4f m_Matrix; // NOTE(justin, mitch) this is derivable but im pretty sure
                                      //                     storing it may be a better idea

        public:
            Transform();
            Transform(Eigen::Vector3f position, Eigen::Vector3f scale, Eigen::Vector3f rotation);

            void SetPosition(Eigen::Vector3f newPosition);
            Eigen::Vector3f GetPosition();

            void SetScale(Eigen::Vector3f newScale);
            Eigen::Vector3f GetScale();

            void SetRotation(Eigen::Vector3f newRotation);
            Eigen::Vector3f GetRotation();

            void UpdateMatrix();

            Eigen::Matrix4f GetMatrix();
        };

    }
}

#endif // __TRANSFORM_HPP__
