#ifndef CRUST_MACROS_H
#define CRUST_MACROS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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




// ###########
// Output
// ###########

#define _print_single(x) printf(_fmt_sqc(x), _fmt_other(x))

#define _GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME // Counts arguments

// Scale if needed
#define _print_1(a)          _print_single(a)
#define _print_2(a, b)       _print_single(a); _print_single(b)
#define _print_3(a, b, c)    _print_single(a); _print_single(b); _print_single(c)
#define _print_4(a, b, c, d) _print_single(a); _print_single(b); _print_single(c); _print_single(d)
#define _print_5(a, b, c, d, e) _print_single(a); _print_single(b); _print_single(c); _print_single(d); _print_single(e)


// Access functions

#define print(...) do { \
    _GET_MACRO(__VA_ARGS__, _print_5, _print_4, _print_3, _print_2, _print_1)(__VA_ARGS__); \
} while(0)

#define println(...) do { \
    print(__VA_ARGS__); \
    printf("\n"); \
} while(0)





// ###########
// Comparison
// ###########

#define _cmp(a, b) _Generic((a) \
    char*: strcmp((a), (b)) == 0, \
    default: (a) == (b) \
)


// Access functions
#define assert_eq(a, b) do { \
	if (!_cmp(a, b)) {
		
	}
}



#endif