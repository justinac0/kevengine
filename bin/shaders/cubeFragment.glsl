#version 330 core

out vec4 FragColor;

in vec3 textureCoords;

uniform samplerCube cubeMap;

void main(void) {
    FragColor = texture(cubeMap, textureCoords);
}