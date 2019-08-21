#include "str.h"

str_t str_new(char src[]) {
    str_t str;
    str.data    = src;
    str.length  = str_length(src);

    return str;
}

void str_del(str_t* src) {
    src->length = 0;
    free(src->data);
}

void str_print(str_t* str) {
    printf("str_length(%d)\n", str->length);
    printf("str: %s\n", str->data);
}

unsigned int str_length(char* src) {
    unsigned int length = 0;
    while (*src != '\0') {
        length++;
        src++;
    }

    return length;
}

void str_sub_string(str_t* dest, unsigned int start, unsigned int end) {
    if (dest->length > 0 && end <= dest->length && start <= end) {
        unsigned int newLength = (end - start) + 1;

        char* newString;
        if ((newString = (char*)malloc(sizeof(char) * newLength + 1)) != NULL) {
            for (int i = 0; i < newLength; i++) {
                newString[i] = dest->data[start+i];
            }
            newString[newLength] = '\0';
        }

        free(dest->data);
        dest->data = &newString[0];
        dest->length  = str_length(dest->data);
    }
}

void str_concat(str_t* dest, char src[]) {
    int len = 0;
    str_length(src);
}
