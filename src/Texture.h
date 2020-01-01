#ifndef TEXTURE_H
#define TEXTURE_H

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

#endif // TEXTURE_H
