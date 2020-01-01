#version 420 core

layout (location = 0) in vec3 in_vertex_positions;

uniform mat4 perspective;
uniform mat4 view;

out vec3 positions;

void main(void) {
    positions = in_vertex_positions;
    gl_Position = (perspective * view * vec4(in_vertex_positions, 1.0f)).xyzw;
}