#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "../../../deps/glad/glad.h"

// memory allocation debugging.
void* u_malloc(size_t size, uint32_t line, const char* file, const char* func);
void* u_calloc(size_t itemCount, size_t size, uint32_t line, const char* file, const char* func);
void* u_realloc(void* ptr, size_t size, uint32_t line, const char* file, const char* func);
void u_free(void* ptr, uint32_t line, const char* file, const char* func);

#ifdef U_MEM_DEBUG
    #warning Memory debugging enabled...

    #define malloc(size)            u_malloc(size, __LINE__, __FILE__, __FUNC__);
    #define calloc(itemCount, size) u_calloc(itemCount, size, __LINE__, __FILE__, __FUNC__);
    #define realloc(ptr, size)      u_realloc(ptr, size, __LINE__, __FILE__, __FUNC__);
    #define free(ptr)               u_free(ptr, __LINE__, __FILE__, __FUNC__);
#endif

// file I/O.
#define MAX_FILE_LINE_WIDTH 512

/* read raw text file and return contents in string form */
char* u_file_read(char* fileLocation);

// wavefront file structure.
typedef struct {
    GLfloat* vertices;
    uint32_t vCount;
    GLfloat* normals;
    uint32_t nCount;
    GLuint* indices;
    uint32_t iCount;
} u_wavefront_t;

u_wavefront_t u_wavefront_load(const char* fileLocation);
void u_wavefront_free(u_wavefront_t* obj);

#endif // UTIL_H
