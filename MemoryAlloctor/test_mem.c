#include "mm.h"
#include "memlib.h"
#include "csapp.h"

int main()
{
    int i = 0;
    int* p = (int*)mm_malloc(10 * sizeof(int));
    for(i = 0; i < 10; ++i)
    {
        p[i] = i + 1;
    }
    
    for (i = 0; i < 10; ++i)
    {
        printf("Addr : Val = 0x%p : %d\n", p + i, p[i]);
    }

    mm_free(p);
    return 0;
}
