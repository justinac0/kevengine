#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MEM_CHECK_ALLOC(ptr) assert(ptr != NULL)
#define MEM_CAST_STRUCT(type) *(type*)

void* mem_debug_malloc(size_t size, int line, const char* file);
void mem_debug_free(void* ptr, int line, const char* file);

#ifdef MEM_DEBUG
    #define malloc(size)    mem_debug_malloc(size, __LINE__, __FILE__);
    #define free(ptr)       mem_debug_free(ptr, __LINE__, __FILE__);
#endif // MEM_DEBUG

#endif // MEM_H
