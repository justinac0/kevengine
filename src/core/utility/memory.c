#include "memory.h"

memory_pool_t memory_pool_create(uint32_t capacity) {
    memory_pool_t mp;
    mp.size     = 0;
    mp.capacity = capacity;
    mp.length   = 0;
    mp.blocks   = (memory_block_t*) malloc(mp.capacity);

    return mp;
}

void memory_pool_destroy(memory_pool_t* mp) {
    free(mp->blocks);

    mp->size     = 0;
    mp->capacity = 0;
    mp->length   = 0;
    mp->blocks   = NULL;
}

void memory_pool_add(memory_pool_t* mp, char tag, uint32_t size, void* data) {
    if (mp->size + size >= mp->capacity) {
        // printf("Memory pool is full...\n");
        return;
    }

    size_t blockSize = size + (sizeof(memory_block_t) - sizeof(void*));

    mp->blocks[mp->length].tag  = tag;
    mp->blocks[mp->length].size = blockSize;
    memcpy(&mp->blocks[mp->length].data, &data, blockSize);

    // printf("::NEW_BLOCK(addr(%p) | size = %d bytes)\n", &mp->blocks[mp->length], blockSize);
    
    mp->size += blockSize;
    mp->length++;
}

void memory_pool_del(memory_pool_t* mp, uint32_t index) {
    mp->blocks[index].tag = MEMORY_BLOCK_TAG_FREE_NOW;
}
