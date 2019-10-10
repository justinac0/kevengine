#version 330 core

out vec4 FragColor;

in vec3 surfaceNormal;
in vec3 toLightVector;

void main(void) {
    vec3 ambient = 0.1f * vec3(0.0f, 0.2f, 0.3f);

    vec3 unitNormal         = normalize(surfaceNormal);
    vec3 unitLightVector    = normalize(toLightVector);

    float nDot1 = dot(unitNormal, unitLightVector);
    float brightness = max(nDot1, 0.0f);
    vec3 diffuse = brightness * vec3(1, 1, 1);

    vec3 debugNormals = (surfaceNormal * -1);

    FragColor = vec4(ambient + diffuse * surfaceNormal, 1.0f);        
}
