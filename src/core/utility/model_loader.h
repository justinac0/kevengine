#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../../../deps/glad/glad.h"
#include "../renderer/mesh.h"
#include "math.h"

#define MAX_FILE_LINE_WIDTH 512

// wavefront file structure.
typedef struct {
    vec3_t*  vertices;
    uint32_t vertCount;
    vec3_t*  normals;
    uint32_t normCount;
    GLuint*  indices;
    uint32_t indCount;
} ml_wavefront_t;

ml_wavefront_t ml_wavefront_load(const char* fileLocation);
void ml_wavefront_free(ml_wavefront_t* obj);

#endif // MODEL_LOADER_H
