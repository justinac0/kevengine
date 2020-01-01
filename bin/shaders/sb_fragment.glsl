#version 420 core

out vec4 FragColor;

in vec3 positions;

vec3 primary = {0.01, 0.01, 0.01};
vec3 secondary = {0.65, 0.65, 0.65};

void main(void) {
    if (positions.y < 0.05) {
        FragColor = vec4(primary, 1.0f);
    } else if (positions.y > 0.5) {
        FragColor = vec4(secondary, 1.0f);
    } else {
        FragColor = vec4(0.5, 0.5, 0.5, 1);
    }
}
