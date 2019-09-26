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

char* u_file_read(char* fileLocation) {
    FILE* fileStream = NULL;
    if ((fileStream = fopen(fileLocation, "r")) == NULL) {
        printf("Failed to open file at location: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    fseek(fileStream, SEEK_SET, SEEK_END);
    uint32_t fileLength = ftell(fileStream);
    rewind(fileStream);

    char* buffer = NULL;
    if ((buffer = (char*)calloc(fileLength + 1, sizeof(char))) == NULL) {
        printf("Cannot allocate memory for file buffer\n");
        exit(EXIT_FAILURE);
    }

    fread(buffer, sizeof(char), fileLength, fileStream);

    fclose(fileStream);

    return buffer;
}
