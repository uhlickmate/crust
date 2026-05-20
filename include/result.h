#ifndef CRUST_RESULT_H
#define CRUST_RESULT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Result(T, E) struct { \
	union { T ok; E err_t; } value; \
	bool is_ok; \
}

/**
 * @brief Unwraps Result.
 * @details If wrapped value is Ok, returns value, else panics.
 * 
 * @param res Result to unwrap
 */
#define unwrap_res(res) ({ \
    __typeof__(res) _res = (res); \
    if (!_res.is_ok) { \
        fprintf(stderr, "PANIC: Attempted unwrap on `Err` result\n"); \
        abort(); \
    } \
    _res.value.ok; \
})

/**
 * @brief Unwraps Result with a message if fails.
 * @details If wrapped value is Ok, returns value, else panics.
 * 
 * @param res Result to unwrap
 */
#define expect_res(res, msg) ({ \
    __typeof__(res) _res = (res); \
    if (!_res.is_ok) { \
        fprintf(stderr, "PANIC: %s\n", (msg)); \
        abort(); \
    } \
    _res.value.ok; \
})

#define is_valid(res) ({ (res).is_ok; })
#define is_err(res) ({ !(res).is_ok; })

#define Ok(val) { .value.ok = (val), .is_ok = true }
#define Err(err) { .value.err_t = (err), .is_ok = false }

#endif