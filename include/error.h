#ifndef CRUST_ERROR_H
#define CRUST_ERROR_H

typedef enum {
	ERR_NONE,
	ERR_GENERIC
} Error;

#define ERROR_LIST(X) \
	X(ERR_NONE, "No errors encountered") \
	X(ERR_GENERIC, "Generic error encountered") 

static inline const char* error_to_string(Error err) {
	static const char* msg_table[] = {
		#define AS_STRING_ARRAY(name, string) [name] = string,
		ERROR_LIST(AS_STRING_ARRAY)
		#undef AS_STRING_ARRAY
	};
	
	if (err < 0 || err >= (sizeof(msg_table) / sizeof(msg_table[0]))) {
		return "Unknown or unmapped crust execution fault";
	}
	return msg_table[err];
}

#endif