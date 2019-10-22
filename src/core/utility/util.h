#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "../../../deps/glad/glad.h"
#include "../renderer/mesh.h"
#include "math.h"

// file I/O.
#define MAX_FILE_LINE_WIDTH 512

/* read raw text file and return contents in string form */
char* u_file_read(char* fileLocation);

// wavefront file structure.
typedef struct {
    vec3_t*  vertices;
    uint32_t vertCount;
    vec3_t*  normals;
    uint32_t normCount;
    GLuint*  indices;
    uint32_t indCount;
} u_wavefront_t;

u_wavefront_t u_wavefront_load(const char* fileLocation);
void u_wavefront_free(u_wavefront_t* obj);

#endif // UTIL_H
