#ifndef CRUST_MACROS_H
#define CRUST_MACROS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Common / shared macros

#define _fmt_sqc(x) _Generic((x), \
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
#define _fmt_other(x) _Generic((x), \
    bool: (x) ? "true" : "false", \
    default: (x) \
)

/**
 * @brief Compare values of `a` & `b` with custom 
 * handling for some data types like strings.
 */
#define _cmp(a, b) _Generic((a), \
    const char*: strcmp((char*)(a), (char*)(b)) == 0, \
    char*: strcmp((char*)(a), (char*)(b)) == 0, \
    default: (a) == (b) \
)




// Output

#define _print_single_fd(fd, x) fprintf(fd, _fmt_sqc(x), _fmt_other(x)) // Print any primitive type with inferred format sequence

#define _GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME // Counts arguments

// Functions for printing set amount of arguments
// Scale if needed
#define _print_1(a)          _print_single_fd(stdou, a)
#define _print_2(a, b)       _print_single_fd(stdou, a); _print_single_fd(stdou, b)
#define _print_3(a, b, c)    _print_single_fd(stdou, a); _print_single_fd(stdou, b); _print_single_fd(stdou, c)
#define _print_4(a, b, c, d) _print_single_fd(stdou, a); _print_single_fd(stdou, b); _print_single_fd(stdou, c); _print_single_fd(stdou, d)
#define _print_5(a, b, c, d, e) _print_single_fd(stdou, a); _print_single_fd(stdou, b); _print_single_fd(stdou, c); _print_single_fd(stdou, d); _print_single_fd(stdou, e)


// Access functions

#define print(...) do { \
    _GET_MACRO(__VA_ARGS__, _print_5, _print_4, _print_3, _print_2, _print_1)(__VA_ARGS__); \
} while(0)

#define println(...) do { \
    print(__VA_ARGS__); \
    printf("\n"); \
} while(0)





// Testing / comparison

// Access functions

/**
 * @brief Asserts expression boolean value, panics & aborts on inequality.
 * 
 * @note Not called `assert` as conflicts C lib
 */
#define assert_true(exp) do { \
    if (!(exp)) { \
        fprintf(stderr, "assertion failed: %s", #exp); \
        fprintf(stderr, "\n  at %s:%d\n", __FILE__, __LINE__); \
        abort(); \
    } \
} while (0)

/**
 * @brief Asserts equality of `a` & `b`, panics & aborts on failure.
 */
#define assert_eq(a, b) do { \
    if (!_cmp(a, b)) { \
        fprintf(stderr, "assertion failed: `assert_eq(%s, %s)`\n", #a, #b); \
        fprintf(stderr, "  left:  "); \
        _print_single_fd(stderr, a); \
        fprintf(stderr, "\n  right: "); \
        _print_single_fd(stderr, b); \
        fprintf(stderr, "\n  at %s:%d\n", __FILE__, __LINE__); \
        abort(); \
    } \
} while (0)




#endif