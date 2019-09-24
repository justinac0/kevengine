#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// memory allocation debugging functions.

// file I/O helper functions.
#define U_FILE_READ_FAIL "READ_FAIL"            // cannot read file from given fileLocation.
#define U_FILE_BUFFER_MEMORY_FAIL "MEMORY_FAIL" // cannot allocate memory for file buffer.

char* u_file_read(char* fileLocation);

#endif // UTIL_H