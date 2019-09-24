#include "util.h"

void* u_malloc(size_t size, uint32_t line, char* file) {
    void* memory = malloc(size);
    
    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- MALLOC::(%p)(Line: %d, File: %s)", line, file);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- MALLOC::(%p)(Line: %d, File: %s)\n", memory, line, file);

    return memory;
}

void* u_calloc(size_t itemCount, size_t size, uint32_t line, char* file) {
    void* memory = calloc(itemCount, size);
    
    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- CALLOC::(%p)(Line: %d, File: %s)", line, file);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- CALLOC::(%p)(Line: %d, File: %s)\n", memory, line, file);

    return memory;
}

void* u_realloc(void* ptr, size_t size, uint32_t line, char* file) {
    void* memory = realloc(ptr, size);

    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- REALLOC::(%p)(Line: %d, File: %s)", line, file);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- REALLOC::(%p)(Line: %d, File: %s)\n", memory, line, file);

    return memory;
}

void u_free(void* ptr, uint32_t line, char* file) {
    free(ptr);
    printf("[SUCCESS] -- FREE::(%p)(Line: %d, File: %s)\n", ptr, line, file);
    ptr = NULL;
}

u_int_list_t u_int_list_new(uint32_t capacity) {
    u_int_list_t list;
    list.length     = 0;
    list.capacity   = capacity;
    list.items      = (int*)malloc(sizeof(int) * list.capacity);

    return list;
}

void u_int_list_add(u_int_list_t* list, int item) {
    if (list->length >= list->capacity) {
        printf("Not enough space left in list...\n");
        return;
    }

    list->items[list->length] = item;
    list->length++;
}

void u_int_list_delete(u_int_list_t* list) {
    free(list->items);
    list->items = NULL;
}

u_float_list_t u_float_list_new(uint32_t capacity) {
    u_float_list_t list;
    list.length     = 0;
    list.capacity   = capacity;
    list.items      = (float*)malloc(sizeof(float) * list.capacity);

    return list;
}

void u_float_list_add(u_float_list_t* list, float item) {
    if (list->length >= list->capacity) {
        printf("Not enough space left in list...\n");
        return;
    }

    list->items[list->length] = item;
    list->length++;
}

void u_float_list_delete(u_float_list_t* list) {
    free(list->items);
    list->items = NULL;
}

char* u_file_read(char* fileLocation) {
    FILE* fileStream = NULL;
    if ((fileStream = fopen(fileLocation, "r")) == NULL) {
        printf("Failed to open file at location: %s\n", fileLocation);
        return U_FILE_READ_FAIL;
    }

    fseek(fileStream, SEEK_SET, SEEK_END);
    uint32_t fileLength = ftell(fileStream);
    rewind(fileStream);

    char* buffer = NULL;
    if ((buffer = (char*)calloc(fileLength + 1, sizeof(char))) == NULL) {
        printf("Cannot allocate memory for file buffer\n");
        return U_FILE_BUFFER_MEMORY_FAIL;
    }

    fread(buffer, sizeof(char), fileLength, fileStream);

    fclose(fileStream);

    return buffer;
}
