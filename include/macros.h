#ifndef CRUST_MACROS_H
#define CRUST_MACROS_H

#include <stdio.h>
#include <stdbool.h>

//
// Output
//
// println, print, errors & such
//

// Both guess type of `x` & choose a format sign
#define _print_fmt(x) _Generic((x), \
    bool: "%s ", \
    char: "%c ", \
    int: "%d ", \
    unsigned int: "%u ", \
    long: "%ld ", \
    unsigned long: "%lu ", \
    float: "%f ", \
    double: "%f ", \
    char*: "%s ", \
    const char*: "%s ", \
    default: "%p " \
)
#define _print_val(x) _Generic((x), \
    bool: (x) ? "true" : "false", \
    default: (x) \
)

#define _print_single(x) printf(_print_fmt(x), _print_val(x))

#define _GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME // Counts arguments

// Scale if needed
#define _print_1(a)          _print_single(a)
#define _print_2(a, b)       _print_single(a); _print_single(b)
#define _print_3(a, b, c)    _print_single(a); _print_single(b); _print_single(c)
#define _print_4(a, b, c, d) _print_single(a); _print_single(b); _print_single(c); _print_single(d)
#define _print_5(a, b, c, d, e) _print_single(a); _print_single(b); _print_single(c); _print_single(d); _print_single(e)

#define print(...) do { \
    _GET_MACRO(__VA_ARGS__, _print_5, _print_4, _print_3, _print_2, _print_1)(__VA_ARGS__); \
} while(0)

#define println(...) do { \
    print(__VA_ARGS__); \
    printf("\n"); \
} while(0)









// #define assert_eq(a, b) do { \

// }

#endif