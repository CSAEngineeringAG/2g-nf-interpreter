//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <ch.h>
#include <stdlib.h>
#include <string.h>

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
