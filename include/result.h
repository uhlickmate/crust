#ifndef CRUST_RESULT_H
#define CRUST_RESULT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Result(T, E) Result_##T##_##E

#define DECLARE_RESULT(T, E) \
    typedef struct { \
        union { \
            T ok; \
            E err_t; \
        } value; \
        bool is_ok; \
    } Result(T, E)

#define Ok(val)  { .value.ok = (val), .is_ok = true }
#define Err(err) { .value.err_t = (err), .is_ok = false }

#define OkExplicit(T, E, val)  ((Result(T, E)) { .value.ok = (val), .is_ok = true })
#define ErrExplicit(T, E, err) ((Result(T, E)) { .value.err_t = (err), .is_ok = false })

#define unwrap_res(res) ({ \
    __typeof__(res) _res = (res); \
    if (!_res.is_ok) { panic("Attempted unwrap on `Err` result"); } \
    _res.value.ok; \
})

#define expect_res(res, msg) ({ \
    __typeof__(res) _res = (res); \
    if (!_res.is_ok) { panic(msg); } \
    _res.value.ok; \
})

#define is_ok(res) (res).is_ok;
#define is_err(res) !(res).is_ok;

DECLARE_RESULT(int, Error);
DECLARE_RESULT(bool, Error);
DECLARE_RESULT(float, Error);
DECLARE_RESULT(char, Error);
DECLARE_RESULT(double, Error);
DECLARE_RESULT(size_t, Error);

#endif