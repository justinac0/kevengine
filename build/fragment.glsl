// fragment shader
#version 330 core

in vec3 colours;
in vec3 normals;
in vec3 lightPosition;
in vec3 fragPosition;
flat in int test;

void main() {
    float ambientStrength = 0.6;
    vec3 ambient = ambientStrength * vec3(0.2,0.2,0.2);

    vec3 normal = normalize(normals);
    vec3 lightDir = normalize(lightPosition + fragPosition);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.8,0.8,0.8);

    vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 1.0); // * normal;
    gl_FragColor = vec4(result, 1.0);
}