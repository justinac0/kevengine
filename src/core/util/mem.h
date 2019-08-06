#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define MEM_CHECK_ALLOC(ptr) assert(ptr != NULL)

void* mem_debug_malloc(size_t size, int line, const char* file);
void mem_debug_free(void* ptr, int line, const char* file);

#ifdef MEM_DEBUG
    #define malloc(size)    mem_debug_malloc(size, __LINE__, __FILE__);
    #define free(ptr)       mem_debug_free(ptr, __LINE__, __FILE__);
#endif // MEM_DEBUG

typedef struct mem_pool_t {
    unsigned int length;
    unsigned int size;
    void** data;
} mem_pool_t;

void mem_pool_create(mem_pool_t* pool, unsigned int size);
void mem_pool_destroy(mem_pool_t* pool);

#endif // MEM_H
