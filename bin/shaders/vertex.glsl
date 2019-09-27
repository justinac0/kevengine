#version 330 core

layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 normals;

uniform mat4 mvp;

void main(void) {
    gl_Position = mvp * vec4(positions, 1.0);
}
