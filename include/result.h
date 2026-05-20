#ifndef CRUST_RESULT_H
#define CRUST_RESULT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Result(T, E) struct { \
	union { T ok; E err; } value; \
	bool is_ok; \
} \

#define unwrap ({ \
    if (!res.is_ok) { \
        fprintf(stderr, "PANIC: Attempted unwrap on `Err` result \n"); \
        exit(1); \
    } \
    res.value.ok; \
})


#define Ok(val) { .value.ok = (val), .is_ok = true }
#define Err(err) { .value.err = (err), .is_ok = false }

#endif