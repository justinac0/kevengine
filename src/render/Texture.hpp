#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <iostream>
#include <string>

#include <glad/glad.h>

class Texture {
private:
    GLuint textureID;

public:
    Texture(const char* path);
    ~Texture();

    void use();
};

#endif // TEXTURE_HPP_
