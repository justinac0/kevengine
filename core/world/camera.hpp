#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <iostream>
#include <cmath>

#include <GLFW/glfw3.h>
#include <Eigen/Core>

namespace kevin {

    namespace world {

        class Camera {
        public:
            Camera(float mouseSensitivity, float moveSpeed);
            ~Camera();

            void Update();

            Eigen::Vector3f GetPosition(void);
            Eigen::Matrix4f GetViewMatrix(void);
            Eigen::Matrix4f GetProjectionMatrix(void);
        private:
            float m_MouseSensitivity;
            float m_MoveSpeed;

            float m_Yaw;
            float m_Pitch;
            float m_Fov;

            Eigen::Vector3f m_Position;
            Eigen::Vector3f m_Forward;
            Eigen::Vector3f m_Up;

            Eigen::Matrix4f m_ProjectionMatrix;
            Eigen::Matrix4f m_ViewMatrix;
        };

    };

};

#endif // CAMERA_HPP_