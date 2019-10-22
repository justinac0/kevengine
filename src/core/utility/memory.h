#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
#define MEMORY_TAG_FREE   0 // empty block
#define MEMORY_TAG_USED   1 // used block
#define MEMORY_TAG_RENDER 2 // block contains render target
#define MEMORY_TAG_RAW    3 // raw data

#define MEMORY_BLOCK_CAST_STRUCT(type, data) (*(type*)data)
#define MEMORY_BLOCK_CAST_TYPE(type, data) ((type*)data)

#define MEMORY_1KB 1000

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

memory_pool_t u_memory_pool_create(uint32_t capacity);
void u_memory_pool_destroy(memory_pool_t* mp);
void u_memory_pool_add(memory_pool_t* mp, char tag, uint32_t size, void* data);
void u_memory_pool_del(memory_pool_t* mp, uint32_t index);

#endif // MEMORY_H
