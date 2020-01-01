#version 330 core

layout (location = 0) in vec3 in_vertex_positions;
// layout (location = 2) in vec3 in_vertex_normals;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;

void main(void) {
    gl_Position = perspective * view * model * vec4(in_vertex_positions, 1.0f);
}