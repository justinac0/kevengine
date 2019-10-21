#include "mesh.h"

mesh_t mesh_wavefront_load(const char* fileLocation) {
    u_wavefront_t obj = u_wavefront_load(fileLocation);

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

    u_wavefront_free(&obj);

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
