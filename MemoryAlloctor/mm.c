#include <stdio.h>
#include <stdlib.h>
#include "mm.h"
#include "memlib.h"

/* 基本常数和宏定义 */
#define WSIZE 4             /* WORD 字大小4字节 */
#define DSIZE 8             /* 双字大小*/
#define CHUNKSIZE (1 << 12) /* 每次扩展堆大小 */

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* 压缩块大小和对应的位标志（空闲/占用）*/
#define PACK(size, alloc)  ((size) | (alloc))

/* 读写在位于地址p处的字内容 */
#define GET(p) (*((unsigned int*)(p)))
#define PUT(p, val) (*(unsigned int*)(p) = (val))

/* 读写位于p处字分配空间大小和对应的标志位 */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* 获取 bp 所指块的头块指针和尾块指针 */ 
#define HDRP(bp) ((char*)(bp) - WSIZE)
#define FTRP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* 获取前一块和后一块的指针 */
#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE((char*)(bp) - WSIZE))
#define PREV_BLKP(bp) ((char*)(bp) - GET_SIZE((char*)(bp) - DSIZE))

static char* heap_listp = 0;

static void* extend_heap(size_t words);
static void* coalesce(void* bp);
static void* find_fit(size_t asize);
static void plac(void* bp, size_t asize);

static void* extend_heap(size_t words)
{
    char* bp;
    size_t size;

    /* 分配存储空间保证双字对齐 */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    
    if ((long)(bp = mem_sbrk(size)) == -1)
    {
        return NULL; 
    }

    /* 初始化块的头部和尾部，还有结尾快 */
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    return coalesce(bp);
}

int mm_init(void)
{
    /* 创建初始空堆 */
    if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void*)-1)
    {
        return -1;
    }

    PUT(heap_listp, 0);
    PUT(heap_listp + 1 * WSIZE, PACK(DSIZE, 1));
    PUT(heap_listp + 2 * WSIZE, PACK(DSIZE, 1));
    PUT(heap_listp + 3 * WSIZE, PACK(0, 1));

    heap_listp += 2 * WSIZE;

    if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
    {
        return -1;
    }

    return 0;
}

static void* coalesce(void* bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc)
    {
        return bp;
    }
    else if (prev_alloc && !next_alloc)
    {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }
    else if (!prev_alloc && next_alloc)
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    else
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
                GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    return bp;
}

void mm_free(void* bp)
{
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

static void* find_fit(size_t asize)
{
    char* bp = heap_listp;
    size_t size;
    size_t alloc;
    size_t end = 0;
    while (1)
    {
        size = GET_SIZE(HDRP(bp));
        alloc = GET_ALLOC(HDRP(bp));
        if (size == 0 && alloc == 1)
        {
            end = 1;
            break;
        }
        else if (size < asize || alloc == 1)
        {
            bp = NEXT_BLKP(bp);
        }
        else
        {
            end = 0;
            break;
        }
    }

    if (end == 1) return NULL;
    else return bp;
}

static void place(void* bp, size_t asize)
{
    size_t originalsize = GET_SIZE(HDRP(bp));
    if (originalsize - asize >= 2 * DSIZE)
    {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(originalsize - asize, 0));
        PUT(FTRP(bp), PACK(originalsize - asize, 0));
    }
    else
    {
        PUT(HDRP(bp), PACK(originalsize, 1));
        PUT(FTRP(bp), PACK(originalsize, 1));
    }
}

void* mm_malloc(size_t size)
{
    size_t asize;       /* 调整尺寸 */
    size_t extendsize;  /* 自动扩展堆如果必要 */
    char* bp;

    if (heap_listp == 0)
    {
        mm_init();
    }

    if (size == 0) return NULL;
    
    if (size <= DSIZE)
    {
        asize = DSIZE;
    }
    else
    {
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
    }

    if ((bp = find_fit(asize)) != NULL)
    {
        place(bp, asize);
        return bp;
    }   

    extendsize = MAX(size, CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
    {
        return NULL;
    }
    place(bp, asize);
    return bp;
}

