#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// memory allocation tools
#define MEMORY_BLOCK_TAG_FREE_LATER 0 // block will be removed on next defrag.
#define MEMORY_BLOCK_TAG_FREE_NOW   1 // block will be removed straight awag.
#define MEMORY_BLOCK_TAG_STATIC     2 // block static through entire execution time.
#define MEMORY_BLOCK_TAG_DYNAMIC    3 // block is temporarily used in execution time.

// these tags should be specific to the renderer, not the memory
#define MEMORY_BLOCK_TAG_RENDER  4 // block contains render target
#define MEMORY_BLOCK_TAG_RAW     5 // raw data

#define MEMORY_BLOCK_CAST_STRUCT(type, data) (*(type*)data)
#define MEMORY_BLOCK_CAST_TYPE(type, data)   ((type*)data)

#define MEMORY_1MB 1000000

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

memory_pool_t memory_pool_create(uint32_t capacity);
void memory_pool_destroy(memory_pool_t* mp);
void memory_pool_add(memory_pool_t* mp, char tag, uint32_t size, void* data);
void memory_pool_del(memory_pool_t* mp, uint32_t index);

#endif // MEMORY_H
