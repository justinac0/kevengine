#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_FILE_LINE_WIDTH 512
char* file_read(char* fileLocation);

#endif // FILE_IO_H
