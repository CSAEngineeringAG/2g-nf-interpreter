//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <ch.h>
#include <stdlib.h>
#include <string.h>
#include <nanoHAL_v2.h>

void* platform_malloc(size_t size) {
    return chHeapAlloc(NULL, size);
}

void  platform_free(void*  ptr) {
    chHeapFree(ptr);
}

void* platform_realloc(void*  ptr, size_t size) {
    (void)size;
    return ptr;
}

void* malloc(size_t size) {
    return platform_malloc(size);
}

void free (void * ptr) {
	if (ptr != NULL) {
		platform_free(ptr);
	}
}

void* calloc (size_t num, size_t size) {
    void* p = platform_malloc(num*size);
    memset(p,0,num*size);
    return p;
}

void *realloc( void *ptr, size_t new_size ){
	if (ptr == NULL) {
		// pointer is null --> allocate memory block
		return platform_malloc(new_size);
	} else {
		if (new_size == 0) {
			// new size is 0 --> free memory
			platform_free(ptr);
			return NULL;
		} else {
			// pointer is not NULL and new size is not 0 --> allocate new memory block
			ASSERT(false);
			return ptr;
		}
	}
}
