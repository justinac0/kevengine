#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace kevin {

    namespace renderer {

        class Renderer {
        public:
            Renderer(uint32_t width, uint32_t height);
            ~Renderer();

            void UpdateWindow();

            bool GetWindowShouldClose();
            GLFWwindow* GetWindowHandle();

        private:
            bool m_IsRunning;
            GLFWwindow* m_Window;
        };

    }
}
#endif // __RENDERER_HPP__
