#include "util.h"

void* u_malloc(size_t size, uint32_t line, const char* file, const char* func) {
    void* memory = malloc(size);
    
    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- MALLOC::(%p)(Line: %d, File: %s, Function: %s)", line, file, func);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- MALLOC::(%p)(Line: %d, File: %s, Function: %s)\n", memory, line, file, func);

    return memory;
}

void* u_calloc(size_t itemCount, size_t size, uint32_t line, const char* file, const char* func) {
    void* memory = calloc(itemCount, size);
    
    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- CALLOC::(%p)(Line: %d, File: %s, Function: %s)", line, file, func);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- CALLOC::(%p)(Line: %d, File: %s, Function: %s)\n", memory, line, file, func);

    return memory;
}

void* u_realloc(void* ptr, size_t size, uint32_t line, const char* file, const char* func) {
    void* memory = realloc(ptr, size);

    if (memory == NULL) {
        fprintf(stderr, "[FAILED] -- REALLOC::(%p)(Line: %d, File: %s, Function: %s)", line, file, func);
        exit(EXIT_FAILURE);
    }

    printf("[SUCCESS] -- REALLOC::(%p)(Line: %d, File: %s, Function: %s)\n", memory, line, file, func);

    return memory;
}

void u_free(void* ptr, uint32_t line, const char* file, const char* func) {
    free(ptr);
    printf("[SUCCESS] -- FREE::(%p)(Line: %d, File: %s, Function: %s)\n", ptr, line, file, func);
    ptr = NULL;
}

memory_pool_t u_memory_pool_create(uint32_t capacity) {
    memory_pool_t mp;
    mp.size     = 0;
    mp.capacity = capacity;
    mp.length   = 0;
    mp.blocks   = (memory_block_t*) malloc(mp.capacity);

    return mp;
}

void u_memory_pool_destroy(memory_pool_t* mp) {
    free(mp->blocks);

    mp->size     = 0;
    mp->capacity = 0;
    mp->length   = 0;
    mp->blocks   = NULL;
}

void u_memory_pool_add(memory_pool_t* mp, char tag, uint32_t size, void* data) {
    if (mp->size + size >= mp->capacity) {
        printf("Memory pool is full...\n");
        return;
    }

    size_t blockSize = size + (sizeof(memory_block_t) - sizeof(void*));

    mp->blocks[mp->length].tag  = tag;
    mp->blocks[mp->length].size = blockSize;
    memcpy(&mp->blocks[mp->length].data, &data, blockSize);

    printf("::NEW_BLOCK(addr(%p) | size = %d bytes)\n", &mp->blocks[mp->length], blockSize);
    
    mp->size += blockSize;
    mp->length++;
}

void u_memory_pool_rem(memory_pool_t* mp, uint32_t index) {
    
}

// void u_memory_pool_defrag(memory_pool_t* mp) { }

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

u_wavefront_t u_wavefront_load(const char* fileLocation) {
    u_wavefront_t obj;
    obj.vertices    = NULL;
    obj.vertCount   = 0;
    obj.normals     = NULL;
    obj.normCount   = 0;
    obj.indices     = NULL;
    obj.indCount    = 0;

    uint32_t vP = 0;
    float v1,v2,v3;

    uint32_t nP = 0;
    float n1, n2, n3;

    uint32_t fP = 0;
    int f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;

    FILE* fileStream = fopen(fileLocation, "r");
    if (fileStream == NULL) {
        fprintf(stderr, "Failed to find file: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    char lineBuffer[MAX_FILE_LINE_WIDTH];
    while (fgets(lineBuffer, MAX_FILE_LINE_WIDTH, fileStream)) {
        if (sscanf(lineBuffer, "v %f %f %f", &v1, &v2, &v3) == 3) {
            obj.vertCount++;
        }

        if (sscanf(lineBuffer, "vn %f %f %f", &n1, &n2, &n3) == 3) {
            obj.normCount++;
        }

        if (sscanf(lineBuffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9) == 9) {
            obj.indCount+=3;
        }
    }

    rewind(fileStream);

    obj.vertices    = (vec3_t*) malloc(sizeof(vec3_t) * obj.vertCount);
    obj.normals    = (vec3_t*) malloc(sizeof(vec3_t) * obj.normCount);
    obj.indices     = (GLuint*) malloc(sizeof(GLuint) * obj.indCount);

    while (fgets(lineBuffer, MAX_FILE_LINE_WIDTH, fileStream)) {
        if (sscanf(lineBuffer, "v %f %f %f", &v1, &v2, &v3) == 3) {
            obj.vertices[vP] = (vec3_t){ v1, v2, v3 };
            vP++;
        }

        if (sscanf(lineBuffer, "vn %f %f %f", &n1, &n2, &n3) == 3) {
            obj.normals[nP] = (vec3_t){ n1, n2, n3 };
            nP++;
        }

        if (sscanf(lineBuffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9) == 9) {
            obj.indices[fP]     = f1;
            obj.indices[fP+1]   = f4;
            obj.indices[fP+2]   = f7;
            fP += 3;
        }
    }

    if (fclose(fileStream) != 0) {
        fprintf(stderr, "File was not closed properly: %s\n", fileLocation);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < obj.indCount; i++) {
        obj.indices[i]--;
    }

    return obj;
}

void u_wavefront_free(u_wavefront_t* obj) {
    free(obj->vertices);
    free(obj->normals);
    free(obj->indices);

    obj->vertices   = NULL;
    obj->normals    = NULL;
    obj->indices    = NULL;
}
