/*
 * gwmem-native.h - memory managment wrapper functions, native flavor
 *
 * Lars Wirzenius
 */

#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "gwlib.h"


void *gw_native_malloc(size_t size) {
	void *ptr;
	
	/* ANSI C89 says malloc(0) is implementation-defined.  Avoid it. */
	gw_assert(size > 0);
	
	ptr = malloc(size);
	if (ptr == NULL)
		panic(errno, "Memory allocation of %lu bytes failed", 
			(unsigned long) size);
	
	return ptr;
}


void *gw_native_realloc(void *ptr, size_t size) {
	void *new_ptr;
	
	gw_assert(size > 0);

	new_ptr = realloc(ptr, size);
	if (new_ptr == NULL)
		panic(errno, "Memory re-allocation of %lu bytes failed", 
			(unsigned long) size);
	
	return new_ptr;
}


void  gw_native_free(void *ptr) {
	free(ptr);
}


char *gw_native_strdup(const char *str) {
	char *copy;
	
	gw_assert(str != NULL);

	copy = gw_native_malloc(strlen(str) + 1);
	strcpy(copy, str);
	return copy;
}
