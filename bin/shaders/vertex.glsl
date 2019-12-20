#version 330 core

layout (location = 0) in vec3 in_vertex_positions;
layout (location = 1) in vec3 in_vertex_normals;

out vec3 surfaceNormal;
out vec3 toLightVector;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPosition;

void main(void) {
    vec4 worldPosition  = model * vec4(in_vertex_positions, 1.0f);
    gl_Position         = perspective * view * model * worldPosition;

    surfaceNormal   = (model * vec4(in_vertex_normals, 0.0)).xyz;
    toLightVector   = lightPosition - worldPosition.xyz;
}