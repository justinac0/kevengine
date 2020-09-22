#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <iostream>
#include <vector>

#include <glad/glad.h>

namespace kevin {

    namespace renderer {

        // deprecate this poop
        class Mesh {
        public:
            Mesh();
            Mesh(std::vector<float> vertices, std::vector<float> colours, std::vector<int> indices);
            ~Mesh();

            void DrawElements(); // indexed renderering
            void DrawArrays();   // non-indexed renderering

            GLuint GetVaoID();
        private:
            uint32_t m_vertCount;
            uint32_t m_idxCount;
            GLuint   m_vaoID;
        };

    }

}

#endif // __MESH_HPP__
