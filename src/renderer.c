#define MAX_FILE_LINE_WIDTH 512
#include "renderer.h"

GLuint r_vertex_buffer_create(void) {
    GLuint vaoID;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    return vaoID;
}

GLuint r_buffer_create_c(uint32_t size, GLchar* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint r_buffer_create_s(uint32_t size, GLshort* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint r_buffer_create_i(uint32_t size, GLuint* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

GLuint r_buffer_create_f(uint32_t size, GLfloat* data, GLenum target, GLenum usage) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, usage);

    return buffer;
}

void r_buffer_delete(GLuint* bufferObject) {
    glDeleteBuffers(1, bufferObject);
}

GLuint r_shader_compile(const char* fileLocation, const int shaderType) {
    GLuint shaderID = glCreateShader(shaderType);
    uint32_t result, length;

    char* source = u_file_read(fileLocation);
    length = strlen(source);

    glShaderSource(shaderID, 1, (const char**)&source, &length);
    glCompileShader(shaderID);
    free(source);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

        char* errorLog = (char*)malloc(length);

        glGetShaderInfoLog(shaderID, length, &result, errorLog);
        glDeleteShader(shaderID);

        fprintf(stderr, "Shader compilation failed: %s\n", errorLog);
        free(errorLog);

        return 0;
    }

    return shaderID;
}

GLuint r_shader_load(const char* vertexFileLocation, const char* fragmentFileLocation) {
    GLuint vertID = r_shader_compile(vertexFileLocation,   GL_VERTEX_SHADER);
    GLuint fragID = r_shader_compile(fragmentFileLocation, GL_FRAGMENT_SHADER);

    GLuint shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertID);
    glAttachShader(shaderProgramID, fragID);
    glLinkProgram(shaderProgramID);

    glDetachShader(shaderProgramID, vertID);
    glDetachShader(shaderProgramID, fragID);

    glDeleteShader(vertID);
    glDeleteShader(fragID);

    return shaderProgramID;
}

void r_shader_use(GLuint shaderProgramID) {
    glUseProgram(shaderProgramID);
}

r_mesh_t r_mesh_obj(const char* fileLocation) {
    double beginTime    = glfwGetTime();
    double endTime      = 0;

    uint32_t vCount = 0;
    uint32_t vP     = 0;
    float v1,v2,v3;

    uint32_t nCount = 0;
    uint32_t nP     = 0;
    float n1, n2, n3;

    uint32_t fCount = 0;
    uint32_t fP     = 0;
    int f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;

    FILE* fileStream = fopen(fileLocation, "r");
    if (fileStream == NULL) {
        fprintf(stderr, "Failed to find file: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    char lineBuffer[MAX_FILE_LINE_WIDTH];
    while (fgets(lineBuffer, MAX_FILE_LINE_WIDTH, fileStream)) {
        { // get vertex positions
            if (sscanf(lineBuffer, "v %f %f %f", &v1, &v2, &v3) == 3) {
                vCount += 3;
            }
        }

        { // get normals
            if (sscanf(lineBuffer, "vn %f %f %f", &n1, &n2, &n3) == 3) {
                nCount += 3;
            }
        }

        { // get winding order indices
            // vertex indices
            if (sscanf(lineBuffer, "f %d %d %d", &f1, &f2, &f3) == 3) {
                fCount += 3;
            }

            // vertex texture coordinate indices
            if (sscanf(lineBuffer, "f %d/%d %d/%d %d/%d", &f1, &f2, &f3, &f4, &f5, &f6) == 6) {
                fCount += 3;
            }

            // vertex normal indices
            if (sscanf(lineBuffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9) == 9) {
                fCount += 3;
            }

            // vertex normal indices without texture coordinate indices
            if (sscanf(lineBuffer, "f %d//%d %d//%d %d//%d", &f1, &f2, &f3, &f4, &f5, &f6) == 6) {
                fCount += 3;
            }
        }
    }

    rewind(fileStream);

    GLfloat* vertices   = (GLfloat*)malloc(sizeof(GLfloat) * vCount);
    GLfloat* normals    = (GLfloat*)malloc(sizeof(GLfloat) * nCount);
    GLuint* indices     = (GLuint*)malloc(sizeof(GLuint) * fCount);

    while (fgets(lineBuffer, MAX_FILE_LINE_WIDTH, fileStream)) {
        { // get vertex positions
            if (sscanf(lineBuffer, "v %f %f %f", &v1, &v2, &v3) == 3) {
                // printf("v %f %f %f\n", v1, v2, v3);
                vertices[vP]    = v1;
                vertices[vP+1]  = v2;
                vertices[vP+2]  = v3;
                vP += 3;
            }
        }

        { // get normals
            if (sscanf(lineBuffer, "vn %f %f %f", &n1, &n2, &n3) == 3) {
                // printf("vn %f %f %f\n", n1, n2, n3);
                normals[nP]     = n1;
                normals[nP+1]   = n2;
                normals[nP+2]   = n3;
                nP += 3;
            }
        }

        { // get winding order indices
            // vertex indices
            if (sscanf(lineBuffer, "f %d %d %d", &f1, &f2, &f3) == 3) {
                // printf("f %d %d %d\n", f1, f2, f3);
                indices[fP]     = f1;
                indices[fP+1]   = f2;
                indices[fP+2]   = f3;
                fP += 3;
            }

            // vertex texture coordinate indices
            if (sscanf(lineBuffer, "f %d/%d %d/%d %d/%d", &f1, &f2, &f3, &f4, &f5, &f6) == 6) {
                // printf("f %d %d %d\n", f1, f3, f5);
                indices[fP]     = f1;
                indices[fP+1]   = f3;
                indices[fP+2]   = f5;
                fP += 3;
            }

            // vertex normal indices
            if (sscanf(lineBuffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9) == 9) {
                // printf("f %d %d %d\n", f1, f4, f7);
                indices[fP]     = f1;
                indices[fP+1]   = f4;
                indices[fP+2]   = f7;
                fP += 3;
            }

            // vertex normal indices without texture coordinate indices
            if (sscanf(lineBuffer, "f %d//%d %d//%d %d//%d", &f1, &f2, &f3, &f4, &f5, &f6) == 6) {
                // printf("f %d %d %d\n", f1, f3, f5);
                indices[fP]     = f1;
                indices[fP+1]   = f3;
                indices[fP+2]   = f5;
                fP += 3;
            }
        }
    }

    if (fclose(fileStream) != 0) {
        fprintf(stderr, "File was not closed properly: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < fCount; i++) {
        indices[i]--;
    }

    r_mesh_t mesh;
    mesh.vaoID = r_vertex_buffer_create();

    GLuint vboID = r_buffer_create_f(sizeof(GLfloat) * vCount, vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    GLuint nboID = r_buffer_create_f(sizeof(GLfloat) * nCount, normals, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);

    GLuint iboID = r_buffer_create_i(sizeof(GLuint) * fCount, indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    mesh.iCount = fCount;
    mat4x4_identity(mesh.modelMatrix.v);

    free(vertices);
    free(normals);
    free(indices);

    endTime = glfwGetTime();
    printf("loading (%s) in %f seconds.\n", fileLocation, endTime - beginTime);

    return mesh;
}

void r_mesh_draw(r_mesh_t* mesh) {
    glBindVertexArray(mesh->vaoID);
    glDrawElements(GL_TRIANGLES, mesh->iCount, GL_UNSIGNED_INT, NULL);
}
