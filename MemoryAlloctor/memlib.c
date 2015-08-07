#include "csapp.h"

#define MAX_HEAP (1 << 20)

/* 私有全局变量 */
static char* mem_heap = 0; /* 指向堆的首字节*/
static char* mem_brk;  /* 指向堆的最后一个字节 */
static char* mem_max_addr; /* 堆的最大虚拟内存 */

/* 初始化内存系统 */
void mem_init(void)
{
    mem_heap = (char*)Malloc(MAX_HEAP);
    mem_brk = (char*)mem_heap;
    mem_max_addr = (char*)(mem_heap + MAX_HEAP);
}

/* 扩展当前堆 incr 个字节, 返回扩展后堆的首字节地址 */
void* mem_sbrk(int incr)
{
    if (mem_heap == 0)
    {
        mem_init();
    }
    char* old_brk = mem_brk;

    if (incr < 0 || (mem_brk + incr > mem_max_addr))
    {
        errno = ENOMEM;
        fprintf(stderr, "ERROR: mem_sbrk failed: Ran out of Memory ...\n");
        return (void*)-1;
    }

    mem_brk += incr;
    return (void*)old_brk;
}
