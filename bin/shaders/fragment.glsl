#version 330 core

out vec4 FragColor;
in vec3 colorData;

void main(void) {
    FragColor = vec4(colorData, 1.0);
}
