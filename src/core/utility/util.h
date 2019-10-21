#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "../../../deps/glad/glad.h"
#include "../renderer/mesh.h"
#include "math.h"

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

// memory allocation tools
#define MEMORY_BLOCK_TAG_EMPTY 0
#define MEMORY_BLOCK_TAG_USED  1

#define MEMORY_CSTCT(type, data) (*(type*)data) // cast memory pool block to correct type if type stored is a struct
#define MEMORY_CTYPE(type, data) ((type*)data) // case memory pool block to correct type if type stored is non-struct

typedef struct {
    uint32_t tag;  // tags determine what happens with this block at run-time.
    uint32_t size; // constant size in bytes of the data (sizeof(memory_block_t - sizeof(void*)) + size).
    void* data;    // data to be placed in block.
} memory_block_t;

typedef struct {
    uint32_t        size;     // current memory used in pool.
    uint32_t        capacity; // size of memory pool in bytes.
    uint32_t        length;   // current amount of items in pool.
    memory_block_t* blocks;   // collection of memory blocks.
} memory_pool_t;

memory_block_t u_memory_block_create(uint32_t tag, uint32_t size, void* data);
void u_memory_block_free(memory_block_t* block);
memory_pool_t u_memory_pool_create(uint32_t capacity);
void u_memory_pool_destroy(memory_pool_t* mp);
void u_memory_pool_add(memory_pool_t* mp, uint32_t size, void* data);

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
