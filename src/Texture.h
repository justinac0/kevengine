#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <glad/glad.h>

// #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

class Texture {
private:
    GLuint textureID;

public:
    Texture(const char* path);
    ~Texture();

    void use();
};

#endif // TEXTURE_H
