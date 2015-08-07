#ifndef MM_H_
#define MM_H_
#include "csapp.h"

int mm_init(void);
void* mm_malloc(size_t size);
void mm_free(void* bp);

#endif // MM_H_
