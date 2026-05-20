#ifndef CRUST_OPTION_H
#define CRUST_OPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Option(T) struct { \
	T value; \
	bool is_some; \
}

#define unwrap_opt(opt) ({ \
    __typeof__(opt) _opt = (opt); \
    if (!_opt.is_some) { \
        fprintf(stderr, "PANIC: Attempted unwrap on `None` option\n"); \
        exit(1); \
    } \
    _opt.value; \
})

#define expect_opt(opt, msg) ({ \
    __typeof__(opt) _opt = (opt); \
    if (!_opt.is_some) { \
        fprintf(stderr, "PANIC: %s\n", msg); \
        exit(1); \
    } \
    _opt.value; \
})

#define is_some(opt) ({ (opt).is_some; })
#define is_none(opt) ({ !(opt).is_some; })

#define Some(val) { .value = (val), .is_some = true }
#define None { .is_some = false }



#endif