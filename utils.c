#include "utils.h"
#include "stdint.h"
#include "kmalloc.h"

void kmemcpy(void* dest, const void* src, uint32_t count) {
    char* d = (char*)dest;
    char* s = (char*)src;
    for (uint32_t i = 0; i < count; i++)
        d[i] = s[i];
}

