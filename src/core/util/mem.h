#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>

void* mem_debug_malloc(size_t size, int line, const char* file);
void mem_debug_free(void* ptr, int line, const char* file);

#ifdef MEM_DEBUG
    #define malloc(size)    mem_debug_malloc(size, __LINE__, __FILE__);
    #define free(ptr)       mem_debug_free(ptr, __LINE__, __FILE__);
#endif // MEM_DEBUG

typedef struct mem_list_t {
    unsigned int    length;
    unsigned int    dataTypeSize;
    void*           data;
} mem_list_t;

mem_list_t mem_list_alloc(unsigned int dataTypeSize, unsigned int length);
void mem_list_free(mem_list_t* list);
void mem_list_set(mem_list_t* list, void* item, unsigned int index);

typedef struct mem_block_t {
    unsigned int size;
    void* data;
} mem_block_t;

typedef struct mem_pool_t {
    unsigned int length;
    unsigned int size;
    mem_block_t* blocks;
} mem_pool_t;



#endif // MEM_H
