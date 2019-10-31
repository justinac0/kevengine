#include "model_loader.h"

ml_wavefront_t ml_wavefront_load(const char* fileLocation) {
    ml_wavefront_t obj;
    obj.vertices    = NULL;
    obj.vertCount   = 0;
    obj.normals     = NULL;
    obj.normCount   = 0;
    obj.indices     = NULL;
    obj.indCount    = 0;

    uint32_t vP = 0;
    float v1,v2,v3;

    uint32_t nP = 0;
    float n1, n2, n3;

    uint32_t fP = 0;
    int f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;

    FILE* fileStream = fopen(fileLocation, "r");
    if (fileStream == NULL) {
        fprintf(stderr, "Failed to find file: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    char lineBuffer[MAX_FILE_LINE_WIDTH];
    while (fgets(lineBuffer, MAX_FILE_LINE_WIDTH, fileStream)) {
        if (sscanf(lineBuffer, "v %f %f %f", &v1, &v2, &v3) == 3) {
            obj.vertCount++;
        }

        if (sscanf(lineBuffer, "vn %f %f %f", &n1, &n2, &n3) == 3) {
            obj.normCount++;
        }

        if (sscanf(lineBuffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9) == 9) {
            obj.indCount+=3;
        }
    }

    rewind(fileStream);

    obj.vertices = (vec3_t*) malloc(sizeof(vec3_t) * obj.vertCount);
    obj.normals  = (vec3_t*) malloc(sizeof(vec3_t) * obj.normCount);
    obj.indices  = (GLuint*) malloc(sizeof(GLuint) * obj.indCount);

    while (fgets(lineBuffer, MAX_FILE_LINE_WIDTH, fileStream)) {
        if (sscanf(lineBuffer, "v %f %f %f", &v1, &v2, &v3) == 3) {
            obj.vertices[vP] = (vec3_t){ v1, v2, v3 };
            vP++;
        }

        if (sscanf(lineBuffer, "vn %f %f %f", &n1, &n2, &n3) == 3) {
            obj.normals[nP] = (vec3_t){ n1, n2, n3 };
            nP++;
        }

        if (sscanf(lineBuffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9) == 9) {
            obj.indices[fP]     = f1;
            obj.indices[fP+1]   = f4;
            obj.indices[fP+2]   = f7;
            fP += 3;
        }
    }

    if (fclose(fileStream) != 0) {
        fprintf(stderr, "File was not closed properly: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < obj.indCount; i++) {
        obj.indices[i]--;
    }

    return obj;
}

void ml_wavefront_free(ml_wavefront_t* obj) {
    free(obj->vertices);
    free(obj->normals);
    free(obj->indices);

    obj->vertices   = NULL;
    obj->normals    = NULL;
    obj->indices    = NULL;
}