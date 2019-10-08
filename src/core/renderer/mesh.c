#include "mesh.h"

mesh_t mesh_wavefront_load(const char* fileLocation) {
    double beginTime    = glfwGetTime();
    double endTime      = 0;

    u_wavefront_t obj = u_wavefront_load(fileLocation);

    mesh_t mesh;
    mesh.vaoID = ogl_vertex_buffer_create();

    GLuint vboID = ogl_buffer_create_f(sizeof(GLfloat) * obj.vCount, obj.vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    GLuint nboID = ogl_buffer_create_f(sizeof(GLfloat) * obj.nCount, obj.normals, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);

    GLuint iboID = ogl_buffer_create_i(sizeof(GLuint) * obj.iCount, obj.indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    mesh.iCount = obj.iCount;
    mat4x4_identity(mesh.modelMatrix.v);

    u_wavefront_free(&obj);

    endTime = glfwGetTime();
    printf("loading (%s) in %f seconds.\n", fileLocation, endTime - beginTime);

    return mesh;
}
