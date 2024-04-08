/*
 * vim: filetype=c:fenc=utf-8:ts=4:et:sw=4:sts=4
 */
#include <inttypes.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <sys/mman.h>
#include <syscall.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "graphics.h"

extern void *tlsf_create_with_pool(void *mem, size_t bytes);
extern void *g_heap;

void tsk_foo(void *pv);

void sort_bubble(int ary[]);

int ary[300];
/**
 * GCC insists on __main
 *    http://gcc.gnu.org/onlinedocs/gccint/Collect2.html
 */
void __main()
{
    size_t heap_size = 32 * 1024 * 1024;
    void *heap_base = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    g_heap = tlsf_create_with_pool(heap_base, heap_size);
}

/**
 * 第一个运行在用户模式的线程所执行的函数
 */
void main(void *pv)
{
    srand(time(NULL));
    for (int i = 0, temp; i < 300; i++)
    {
        temp = rand() % 200;
        ary[i] = temp;
    }

    int mode = 0x143;
    init_graphic(mode);
    line(200, 0, 200, 600, RGB(255, 0, 0));

    unsigned char *stack_foo;
    unsigned int stack_size = 1024 * 1024;
    stack_foo = (unsigned char *)malloc(stack_size);

    int tid_foo;
    tid_foo = task_create(stack_foo + stack_size, &tsk_foo, (void *)0);
    task_wait(tid_foo, NULL);
    free(stack_foo);
    while (1)
        ;
    task_exit(0);
}

void tsk_foo(void *pv)
{

    int gap = 2;
    for (int i = 0; i < 300; i++)
    {
        line(0, i * gap, ary[i], i * gap, RGB(255, 0, 0));
    }
    sort_bubble2(ary);
    task_exit(0);
}

void sort_bubble(int ary[])
{
    int i, j, temp = 0;
    int gap = 2;

    for (i = 1; i < 300; i++)
    {
        for (j = i; j > 0; j--)
        {
            if (ary[j] < ary[j - 1])
            {
                line(0, (j - 1) * gap, ary[j - 1], (j - 1) * gap, RGB(0, 0, 0));
                temp = ary[j];
                ary[j] = ary[j - 1];
                ary[j - 1] = temp;
                line(0, (j - 1) * gap, ary[j - 1], (j - 1) * gap, RGB(255, 0, 0));

                line(0, j * gap, ary[j], j * gap, RGB(255, 0, 0));
            }
        }
    }
}
void sort_bubble2(int ary[])
{
    int i, j, temp = 0;
    int gap = 2;

    for (i = 1; i < 300; i++)
    {
        for (j = i; j > 0; j--)
        {
            if (ary[j] < ary[j - 1])
            {
                line(200, (j - 1) * gap, 200 + ary[j - 1], (j - 1) * gap, RGB(0, 0, 0));
                temp = ary[j];
                ary[j] = ary[j - 1];
                ary[j - 1] = temp;
                line(200, (j - 1) * gap, 200 + ary[j - 1], (j - 1) * gap, RGB(255, 0, 0));

                line(200, j * gap, 200 + ary[j], j * gap, RGB(255, 0, 0));
            }
        }
    }
}