#version 330 core

layout (location = 0) in vec3 in_positions;

out vec3 textureCoords;

uniform mat4 perspective;
uniform mat4 view;

void main(void) {
    textureCoords = in_positions;
    gl_Position = (perspective * view * vec4(in_positions, 1.0f)).xyzw;
}