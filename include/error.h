#ifndef CRUST_ERROR_H
#define CRUST_ERROR_H

typedef enum {
	ERR_NONE,
} ErrType;

typedef struct {
	ErrType type;
	const char *msg;
} Err;

#endif