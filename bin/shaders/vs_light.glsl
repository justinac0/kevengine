#version 330 core

layout (location = 0) in vec3 in_vertex_positions;
layout (location = 1) in vec3 in_normals_positions;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void) {
    vec4 worldPosition = model * vec4(in_vertex_positions, 1.0f);
    gl_Position = projection * view * model * worldPosition;
}
