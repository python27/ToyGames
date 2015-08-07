#ifndef MEMLIB_H_
#define MEMLIB_H_

#include "csapp.h"

void* mem_init(void);
void* mem_sbrk(int incr);

#endif // MEMLIB_H_
