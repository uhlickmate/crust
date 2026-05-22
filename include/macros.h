	#ifndef CRUST_MACROS_H
	#define CRUST_MACROS_H

	#include <stdio.h>
	#include <stdbool.h>
	#include <string.h>

	#include "config.h"

	// Common / shared macros

	#define _fmt_sqc(x) _Generic((x), \
		bool: "%s", \
		char: "%c", \
		int: "%d", \
		unsigned int: "%u", \
		long: "%ld", \
		unsigned long: "%lu", \
		float: "%f", \
		double: "%f", \
		char*: "%s", \
		const char*: "%s", \
		default: "%p" \
	)
	#define _fmt_other(x) _Generic((x), \
		bool: (x) ? "true" : "false", \
		default: (x) \
	)


	#define _cmp(a, b) _Generic((a), \
		const char*: strcmp((char*)(a), (char*)(b)) == 0, \
		char*: strcmp((char*)(a), (char*)(b)) == 0, \
		default: (a) == (b) \
	)





	#define _print_single(fd, x) fprintf(fd, _fmt_sqc(x), _fmt_other(x)) // Print any primitive type with inferred format sequence
	#define _eprint_single(fd, x) do { \
		fprintf(fd, FG_RED); \
		fprintf(fd, _fmt_sqc(x), _fmt_other(x)); \
		fprintf(fd, FG_RESET); \
	} while(0)

	#define _GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME // Counts arguments

	// Functions for printing set amount of arguments
	// Scale if needed

	// Regular print
	#define _print_1(a)          _print_single(stdout, a)
	#define _print_2(a, b)       _print_single(stdout, a); _print_single(stdout, b)
	#define _print_3(a, b, c)    _print_single(stdout, a); _print_single(stdout, b); _print_single(stdout, c)
	#define _print_4(a, b, c, d) _print_single(stdout, a); _print_single(stdout, b); _print_single(stdout, c); _print_single(stdout, d)
	#define _print_5(a, b, c, d, e) _print_single(stdout, a); _print_single(stdout, b); _print_single(stdout, c); _print_single(stdout, d); _print_single(stdout, e)
	// White eprint
	#define _eprint_1(a)          _print_single(stderr, a)
	#define _eprint_2(a, b)       _print_single(stderr, a); _print_single(stderr, b)
	#define _eprint_3(a, b, c)    _print_single(stderr, a); _print_single(stderr, b); _print_single(stderr, c)
	#define _eprint_4(a, b, c, d) _print_single(stderr, a); _print_single(stderr, b); _print_single(stderr, c); _print_single(stderr, d)
	#define _eprint_5(a, b, c, d, e) _print_single(stderr, a); _print_single(stderr, b); _print_single(stderr, c); _print_single(stderr, d); _print_single(stderr, e)
	// Red eprint
	#define _erprint_1(a)          _eprint_single(stderr, a)
	#define _erprint_2(a, b)       _eprint_single(stderr, a); _eprint_single(stderr, b)
	#define _erprint_3(a, b, c)    _eprint_single(stderr, a); _eprint_single(stderr, b); _eprint_single(stderr, c)
	#define _erprint_4(a, b, c, d) _eprint_single(stderr, a); _eprint_single(stderr, b); _eprint_single(stderr, c); _eprint_single(stderr, d)
	#define _erprint_5(a, b, c, d, e) _eprint_single(stderr, a); _eprint_single(stderr, b); _eprint_single(stderr, c); _eprint_single(stderr, d); _eprint_single(stderr, e)




	#define print(...) do { \
		_GET_MACRO(__VA_ARGS__, _print_5, _print_4, _print_3, _print_2, _print_1)(__VA_ARGS__); \
	} while(0)

	#define println(...) do { \
		print(__VA_ARGS__); \
		printf("\n"); \
	} while(0)

	#define eprint(...) do { \
		_GET_MACRO(__VA_ARGS__, _eprint_5, _eprint_4, _eprint_3, _eprint_2, _eprint_1)(__VA_ARGS__); \
	} while(0)

	#define eprintln(...) do { \
		eprint(__VA_ARGS__); \
		fprintf(stderr, "\n"); \
	} while(0)

	#define eprint_red(...) do { \
		_GET_MACRO(__VA_ARGS__, _erprint_5, _erprint_4, _erprint_3, _erprint_2, _erprint_1)(__VA_ARGS__); \
	} while(0)

	#define eprintln_red(...) do { \
		eprint_red(__VA_ARGS__); \
		fprintf(stderr, "\n"); \
	} while(0)

	#define assert_true(exp) do { \
		if (!(exp)) { \
			fprintf(stderr, "assertion failed: %s", #exp); \
			fprintf(stderr, "\n  at %s:%d\n", __FILE__, __LINE__); \
			abort(); \
		} \
	} while (0)

	#define assert_eq(a, b) do { \
		if (!_cmp(a, b)) { \
			eprintln("assertion failed: `assert_eq(", #a, ", ", #b, ")`"); \
			eprintln("  left:  ", a); \
			eprintln("  right: ", b); \
			eprintln(" at ", __FILE__, ":", __LINE__); \
			abort(); \
		} \
	} while (0)

	#define assert_eq_msg(a, b, msg) do { \
		if (!_cmp(a, b)) { \
			eprintln((msg)); \
		} \
	} while (0)

	#define assert_ne(a, b) do { \
		if (_cmp(a, b)) { \
			eprintln("assertion failed: `assert_ne(", #a, ", ", #b, ")`"); \
			eprintln("  left:  ", a); \
			eprintln("  right: ", b); \
			eprintln(" at ", __FILE__, ":", __LINE__); \
			abort(); \
		} \
	} while (0)

	#define assert_ne_msg(a, b, msg) do { \
		if (_cmp(a, b)) { \
			eprintln((msg)); \
		} \
	} while (0)

	static inline void panic_zero(void) {
		eprintln("Panic: generic panic message");
		abort();
	}
	static inline void panic_one(const char* msg) {
		eprintln("Panic: ", msg);
		abort();
	}
	#define GET_MACRO(_0, _1, NAME, ...) NAME
	#define panic(...) GET_MACRO(_0, ##__VA_ARGS__, panic_one, panic_zero)(__VA_ARGS__)

	#endif