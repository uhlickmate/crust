#ifndef CRUST_OPTION_H
#define CRUST_OPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Option(T) Option_##T

#define DECLARE_OPTION(T) \
    typedef struct { \
        T value; \
        bool is_some; \
    } Option(T)

#define Some(val) { .value = (val), .is_some = true }
#define None { .is_some = false }

#define SomeExplicit(T, val) ((Option(T)) { .value = (val), .is_some = true })
#define NoneExplicit(T)      ((Option(T)) { .is_some = false })

#define unwrap_opt(opt) ({ \
    __typeof__(opt) _opt = (opt); \
    if (!_opt.is_some) { panic("Attempted unwrap on `None` option"); } \
    _opt.value; \
})

#define expect_opt(opt, msg) ({ \
    __typeof__(opt) _opt = (opt); \
    if (!_opt.is_some) { panic(msg); } \
    _opt.value; \
})

#define is_some(opt) ({ (opt).is_some; })
#define is_none(opt) ({ !(opt).is_some; })

DECLARE_OPTION(int);
DECLARE_OPTION(bool);
DECLARE_OPTION(float);
DECLARE_OPTION(char);
DECLARE_OPTION(double);
DECLARE_OPTION(size_t);

#endif