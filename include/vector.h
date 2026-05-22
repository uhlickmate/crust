#ifndef CRUST_VECTOR_H
#define CRUST_VECTOR_H

#include <stdlib.h>
#include <string.h>

#include "option.h"
#include "macros.h"

// For impl functions, only use 'static inline' if method has no or static type return value
// TODO - call static inline funcs immediatelly

#define Vec(T) Vec_##T

#define DECLARE_VEC(T) \
	typedef struct { \
		T *buf_ptr; \
		size_t len; \
		size_t capacity; \
	} Vec(T);


static inline void _vec_cleanup(void *v) {
    struct { void *buf_ptr; size_t len; size_t capacity; } *vec = v;
    free(vec->buf_ptr);
}
#define Vec_auto(T) __attribute__((cleanup(_vec_cleanup))) Vec(T) // Frees itself automatical



#define Vec_new() { NULL, 0, 0 }

// Size of all allocated memory
#define Vec_sizeof(T, vec) ({ \
	size_t size = sizeof(T); \
	(vec).capacity * size; \
})

static inline void _vec_push_impl(void **buf_ptr, size_t *len, size_t *capacity, void *el, size_t el_type_size) {

	// First push - initialize memory
	if (*capacity == 0) {
		*buf_ptr = malloc(el_type_size * 8); 
		if (*buf_ptr == NULL) {  } // TODO - panic
		*capacity = 8;
	}

	// Full - extend memory
	if (*len == *capacity) {
		void *tmp = realloc(*buf_ptr, el_type_size * *capacity * 2);
		if (tmp == NULL) {  } // TODO - panic
		*buf_ptr = tmp;
		*capacity *= 2;
	}

	memcpy((char *)*buf_ptr + (*len * el_type_size), el, el_type_size);
	(*len)++;
}
#define Vec_push(T, vec, el) ({ \
	T _el = (el); \
	_vec_push_impl((void**)&vec.buf_ptr, &vec.len, &vec.capacity, &(_el), sizeof(T)); \
})

#define Vec_pop(T, vec) ({ \
    ((vec).len == 0) \
        ? NoneExplicit(T) \
        : SomeExplicit(T, (vec).buf_ptr[--(vec).len]); \
})

#define Vec_with_capacity(T, cap) ({ \
	size_t size = sizeof(T); \
	Vec(T) v = { NULL, 0, cap }; \
	v.buf_ptr = malloc(size * cap); \
	v; \
})

static inline void _vec_reserve_impl(void **buf_ptr, size_t *capacity, size_t type_size, size_t add) {
	void *tmp = realloc(*buf_ptr, *capacity * type_size + add * type_size);
	if (tmp == NULL) { panic("`realloc` as NULL pointer at `_vec_reserve_impl`"); }
	*buf_ptr = tmp;
	*capacity += add;
}
#define Vec_reserve(T, vec, add) _vec_reserve_impl((void*)&vec.buf_ptr, &vec.capacity, sizeof(T), add)

static inline void _vec_shrink_to_fit_impl(void **buf_ptr, size_t *len, size_t *capacity, size_t type_size) {
	void *tmp = realloc(*buf_ptr, *len * type_size);
	if (tmp == NULL) { panic("`realloc` as NULL pointer at `_vec_shrink_to_fit_impl`"); }
	*buf_ptr = tmp;
	*capacity = *len;
}
#define Vec_shrink_to_fit(T, vec) _vec_shrink_to_fit_impl((void*)&vec.buf_ptr, &vec.len, &vec.capacity, sizeof(T))

#define Vec_get(T, vec, idx) ({ \
    Option(T) _opt; \
    size_t _idx = (size_t)(idx); \
    if (_idx >= (vec).len) { \
        _opt = NoneExplicit(T); \
    } \
    else { \
        _opt = SomeExplicit(T, (vec).buf_ptr[_idx]); \
    } \
    _opt; \
})



static inline void _vec_insert_impl(void **buf_ptr, size_t *len, size_t *capacity, void* el, size_t el_size, size_t idx) {
	if (idx > *len - 1) { panic("Attempted to insert out of bounds at `_vec_insert_impl` (called by Vec_insert)"); }
	if (*len >= *capacity) { panic("Attempted to insert into a full vector at `_vec_insert_impl` (called by Vec_insert)"); }

	char *buf = (char *)*buf_ptr;

	memmove(
		buf + (idx + 1) * el_size,
		buf + idx * el_size,
		(*len - idx) * el_size
	);

	memcpy(buf + idx * el_size, el, el_size);

	(*len)++;
}
#define Vec_insert(T, vec, el, idx) ({ \
	T _el = (el); \
	_vec_insert_impl((void**)&vec.buf_ptr, &vec.len, &vec.capacity, &(_el), sizeof(T), idx); \
})

// vec = [0, 1, 2, 3, 4, 5, 6]
// len = 7
// capacity = 8
// idx = 2

// Check if vec not empty & if index is valid
// Remove & save element
// Move memory
static inline void _vec_remove_impl(void *res, void **buf_ptr, size_t *len, size_t *capacity, size_t el_size, size_t idx) {
	if (idx > *len - 1) { _opt = NoneExplicit(T) }
	if (*len <= 0) { _opt = NoneExplicit(T) }

	memcpy(opt, *buf_ptr + );
}
#define Vec_remove(T, vec, idx) ({ \
	Option(T) _opt; \
	int res; \
	_vec_remove_impl(&res, (void*)&vec.buf_ptr, &vec.len, &vec.capacity, sizeof(T), idx); \
	_opt; \
})

// Vec_display -> String

DECLARE_VEC(int);
DECLARE_VEC(bool);
DECLARE_VEC(float);
DECLARE_VEC(char);
DECLARE_VEC(double);
DECLARE_VEC(size_t);

#endif