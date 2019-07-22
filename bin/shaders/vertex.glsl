#version 330 core

layout (location = 0) in vec3 positionData;

uniform mat4 mvp;
uniform vec3 color;

out vec3 colorData;

void main(void) {
    gl_Position = mvp * vec4(positionData, 1.0);
    colorData = color;
}
