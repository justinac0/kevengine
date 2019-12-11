#include "mesh.h"

mesh_t mesh_wavefront_load(const char* fileLocation) {
    ml_wavefront_t obj = ml_wavefront_load(fileLocation);

    mesh_t mesh;
    mesh.vaoID          = ogl_vertex_buffer_create();
    mesh.iCount         = obj.indCount;

    GLuint vboID = ogl_buffer_create_f((sizeof(vec3_t) * obj.vertCount), obj.vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint nboID = ogl_buffer_create_f((sizeof(vec3_t) * obj.normCount), obj.normals, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(1);

    GLuint iboID = ogl_buffer_create_i((sizeof(GLuint) * obj.indCount), obj.indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    glBindVertexArray(0);

    ml_wavefront_free(&obj);

    return mesh;
}

mesh_t mesh_primitive_triangle(void) {
    vec3_t vertices[3] = {
        (vec3_t){ -1, 0, 0 },
        (vec3_t){ 0, 1, 0 },
        (vec3_t){ 1, 0, 0 }
    };

    vec3_t normals[3] = {
        m_normal_from_triangle((triangle_t){ vertices[0], vertices[1], vertices[2] }),
        m_normal_from_triangle((triangle_t){ vertices[0], vertices[1], vertices[2] }),
        m_normal_from_triangle((triangle_t){ vertices[0], vertices[1], vertices[2] })
    };

    GLuint indices[3] = { 0, 1, 2 };

    mesh_t mesh;
    mesh.vaoID          = ogl_vertex_buffer_create();
    mesh.iCount         = 3;

    GLuint vboID = ogl_buffer_create_f(sizeof(vec3_t) * 3, vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint nboID = ogl_buffer_create_f(sizeof(vec3_t) * 3, normals, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(1);

    GLuint iboID = ogl_buffer_create_i(sizeof(GLuint) * 3, indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    glBindVertexArray(0);

    return mesh;
}

mesh_t mesh_primitive_cube(void) {
    vec3_t vertices[8] = {
        (vec3_t) { 1,  1, -1},
        (vec3_t) { 1, -1, -1}, 
        (vec3_t) { 1,  1,  1},
        (vec3_t) { 1, -1,  1}, 
        (vec3_t) {-1,  1, -1}, 
        (vec3_t) {-1, -1, -1},
        (vec3_t) {-1,  1,  1},
        (vec3_t) {-1, -1,  1}
    };

    vec3_t normals[6] = {
        (vec3_t){ 0, 1, 0 },
        (vec3_t){ 0, 1, 0 },
        (vec3_t){ 0, 1, 0 },
        (vec3_t){ 0, 1, 0 },
        (vec3_t){ 0, 1, 0 },
        (vec3_t){ 0, 1, 0 }
    };

    GLuint indices[36] = {
        4, 2, 0,
        2, 7, 3,
        6, 5, 7,
        1, 7, 5,
        0, 3, 1,
        4, 1, 5,
        4, 6, 2,
        2, 6, 7,
        6, 4, 5,
        1, 3, 7,
        0, 2, 3,
        4, 0, 1
    };

    mesh_t mesh;
    mesh.vaoID  = ogl_vertex_buffer_create();
    mesh.iCount = 36;

    GLuint vboID = ogl_buffer_create_f(sizeof(vec3_t) * 8, vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint nboID = ogl_buffer_create_f(sizeof(vec3_t) * 6, normals, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(1);

    GLuint iboID = ogl_buffer_create_i(sizeof(GLuint) * 36, indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    glBindVertexArray(0);

    return mesh;
}