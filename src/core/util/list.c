#include "list.h"

void* dmem_malloc(size_t size, int line, const char* file) {
    void* buffer = malloc(size);

    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    printf("::MALLOC::%d::%s\n", line, file);
}

void dmem_free(void* ptr, int line, const char* file) {
    free(ptr);

    printf("::FREE::%d::%s\n", line, file);
}

void list_fixed_create(list_fixed_t* dest, unsigned int dataTypeSize, unsigned int length) {
    dest->dataTypeSize      = dataTypeSize;
    dest->length            = length;
    dest->data              = NULL;
    dest->data              = malloc(dataTypeSize * length);
    if (!dest->data) {
        fprintf(stderr, "Failed to allocated memory.\n");
        exit(EXIT_FAILURE);
    }

    printf("(%p) Create new fixed list of length %d\n", dest->data, dest->length);
}

void list_fixed_free(list_fixed_t* list) {
    list->dataTypeSize  = 0;
    list->length        = 0;
    printf("(%p) Free fixed list\n", list->data);

    free(list->data);
}

void list_fixed_set(list_fixed_t* list, void* item, unsigned int index) {
    list->data[index] = item;
}
