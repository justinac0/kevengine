#include "util.h"

void* u_malloc(size_t size, uint32_t line, const char* file, const char* func) {
    void* memory = malloc(size);
    
    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- MALLOC::(%p)(Line: %d, File: %s, Function: %s)", line, file, func);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- MALLOC::(%p)(Line: %d, File: %s, Function: %s)\n", memory, line, file, func);

    return memory;
}

void* u_calloc(size_t itemCount, size_t size, uint32_t line, const char* file, const char* func) {
    void* memory = calloc(itemCount, size);
    
    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- CALLOC::(%p)(Line: %d, File: %s, Function: %s)", line, file, func);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- CALLOC::(%p)(Line: %d, File: %s, Function: %s)\n", memory, line, file, func);

    return memory;
}

void* u_realloc(void* ptr, size_t size, uint32_t line, const char* file, const char* func) {
    void* memory = realloc(ptr, size);

    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- REALLOC::(%p)(Line: %d, File: %s, Function: %s)", line, file, func);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- REALLOC::(%p)(Line: %d, File: %s, Function: %s)\n", memory, line, file, func);

    return memory;
}

void u_free(void* ptr, uint32_t line, const char* file, const char* func) {
    free(ptr);
    printf("[SUCCESS] -- FREE::(%p)(Line: %d, File: %s, Function: %s)\n", ptr, line, file, func);
    ptr = NULL;
}

char* u_file_read(char* fileLocation) {
    FILE* fileStream = NULL;
    if ((fileStream = fopen(fileLocation, "r")) == NULL) {
        printf("Failed to open file at location: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    fseek(fileStream, SEEK_SET, SEEK_END);
    uint32_t fileLength = ftell(fileStream);
    rewind(fileStream);

    char* buffer = NULL;
    if ((buffer = (char*)calloc(fileLength + 1, sizeof(char))) == NULL) {
        printf("Cannot allocate memory for file buffer\n");
        exit(EXIT_FAILURE);
    }

    fread(buffer, sizeof(char), fileLength, fileStream);

    fclose(fileStream);

    return buffer;
}

u_wavefront_t u_wavefront_load(const char* fileLocation) {
    u_wavefront_t obj;

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

    GLfloat* vertices   = (GLfloat*) malloc(sizeof(GLfloat) * vCount);
    GLfloat* normals    = (GLfloat*) malloc(sizeof(GLfloat) * nCount);
    GLuint* indices     = (GLuint*) malloc(sizeof(GLuint) * fCount);

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

    obj.vertices    = vertices;
    obj.vCount      = vCount;
    obj.normals     = normals;
    obj.nCount      = nCount;
    obj.indices     = indices;
    obj.iCount      = fCount;

    return obj;
}

void u_wavefront_free(u_wavefront_t* obj) {
    free(obj->vertices);
    free(obj->normals);
    free(obj->indices);

    obj->vertices   = NULL;
    obj->normals    = NULL;
    obj->indices    = NULL;
}
