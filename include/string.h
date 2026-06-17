#ifndef CRUST_STRING_H
#define CRUST_STRING_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// #define mostly not needed as String is a solid type

typedef struct {
	char *buf_ptr;
	size_t len;
	size_t capacity;
} String;

static inline void _string_cleanup(void *v) {
    struct { void *buf_ptr; size_t len; size_t capacity; } *vec = v;
    free(vec->buf_ptr);
}
#define String_auto __attribute__((cleanup(_string_cleanup))) String) // Frees itself automatical

static inline String String_new() { return (String){ .buf_ptr = NULL, .capacity = 0, .len = 0 }; }

static inline String String_from(const char* str) { 
	return (String){ .buf_ptr = malloc(strlen(str)), .capacity = strlen(str), .len = strlen(str) } ;
}

static inline String String_with_capacity(size_t capacity) { 
	return (String){ .buf_ptr = calloc(1, capacity), .capacity = capacity, .len = 0 }; 
}

static inline bool String_is_empty(String str) { return (str.len == 0); }



#endif
