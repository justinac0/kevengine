// fragment shader
#version 330

in vec3 colours;
    
void main() {
    gl_FragColor = vec4(colours, 1);
}
