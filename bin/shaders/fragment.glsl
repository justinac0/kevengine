#version 330 core

out vec4 FragColor;

in vec3 surfaceNormal;
in vec3 toLightVector;

in vec3 colors;
float ambient_strength = 0.3f;

void main(void) {
    vec3 ambient = vec3(1.0f, 1.0f, 1.0f) * ambient_strength;

    vec3 unitNormal         = normalize(surfaceNormal);
    vec3 unitLightVector    = normalize(toLightVector);

    float nDot1 = dot(unitNormal, unitLightVector);
    float brightness = max(nDot1, 0.1f);
    vec3 diffuse = brightness * colors;

    vec3 debugNormals = (surfaceNormal * -1);

    FragColor = vec4(ambient + diffuse, 1.0f);
}