#include "str.h"

str_t str_new(char src[]) {
    str_t str;
    str.data    = src;
    str.length  = str_length(src);

    return str;
}

void str_del(str_t* str) {
    str->length = 0;
    free(str->data);
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

void str_sub_string(str_t* src, unsigned int start, unsigned int end) {
    if (src->length > 0 && end <= src->length && start <= end) {
        unsigned int newLength = (end - start) + 1;

        // (note: justin) - a way to do this with out malloc needs to be figured out.
        char* newString;

        if ((newString = (char*)malloc(sizeof(char) * newLength + 1)) != NULL) {
            for (int i = 0; i < newLength; i++) {
                newString[i] = src->data[start+i];
            }
            newString[newLength] = '\0';
        }

        src->data = &newString[0];
        src->length  = str_length(src->data);
    }
}

void str_concat(str_t* dest, str_t* src) {

}
