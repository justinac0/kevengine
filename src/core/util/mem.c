#include "mem.h"

void* mem_debug_malloc(size_t size, int line, const char* file) {
    void* buffer = malloc(size);

    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    printf("::MALLOC::(%s)->[Line %d]\n", file, line);

    return buffer;
}

void mem_debug_free(void* ptr, int line, const char* file) {
    free(ptr);

    printf("::FREE::(%s)->[Line %d]\n", file, line);
}

mem_block_t mem_block_new(unsigned int size, void* data) {
    mem_block_t block;
    block.size = size;
    block.data = data;

    return block;
}

void mem_pool_create(mem_pool_t* pool, unsigned int size) {
    pool->length    = 0;
    pool->size      = size;
    pool->data      = malloc(size);

    MEM_CHECK_ALLOC(pool->data);

    printf("Memory pool was created! (pool: %p | size: %d bytes)\n", pool->data, pool->size);
}

void mem_pool_destroy(mem_pool_t* pool) {
    pool->length    = 0;
    pool->size      = 0;
    free(pool->data);

    printf("Memory pool destroyed! (pool: %p | size: %d bytes)\n", pool->data, pool->size);
}
