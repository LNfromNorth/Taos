#ifndef __TAOS_STRING_H__
#define __TAOS_STRING_H__

#include "stdint.h"

void* memset(void* dst, int c, uint64_t n);
int memcmp(const void* v1, const void* v2, uint64_t n);
void* memcpy(void* dst, const void *src, uint64_t n);
int strncmp(const char* p, const char* q, uint64_t n);
char* strncpy(char* s, const char* t, int n);
char* safestrcpy(char* s, const char* t, int n);
int strlen(const char* s);


#endif
