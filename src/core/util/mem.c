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
