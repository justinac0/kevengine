#version 330 core

layout (location = 0) in vec3 positionData;

uniform mat4 mvp;

void main(void) {
    gl_Position = vec4(positionData, 1.0);
}