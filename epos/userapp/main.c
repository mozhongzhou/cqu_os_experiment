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

void tsk_1(void *pv);
void tsk_2(void *pv);
void sort_bubble1(int ary[]);
void sort_bubble2(int ary[]);

int ary1[300], ary2[300];
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
        temp = rand() % 400;
        ary1[i] = temp;
        ary2[i] = temp;
    }

    int mode = 0x143;
    init_graphic(mode);
    line(400, 0, 400, 600, RGB(255, 0, 0));

    unsigned char *stack_1, *stack_2;
    unsigned int stack_size = 1024 * 1024;
    stack_1 = (unsigned char *)malloc(stack_size);
    stack_2 = (unsigned char *)malloc(stack_size);
    int tid_1, tid_2;

    tid_1 = task_create(stack_1 + stack_size, &tsk_1, (void *)0);
    tid_2 = task_create(stack_2 + stack_size, &tsk_2, (void *)0);
    task_wait(tid_1, NULL);
    task_wait(tid_2, NULL);
    free(stack_1);
    free(stack_2);
    while (1)
        ;
    task_exit(0);
}

void tsk_1(void *pv)
{

    int gap = 2;
    for (int i = 0; i < 300; i++)
    {
        line(0, i * gap, ary1[i], i * gap, RGB(128, 0, 128));
    }
    sort_bubble1(ary1);
    task_exit(0);
}
void tsk_2(void *pv)
{

    int gap = 2;
    for (int i = 0; i < 300; i++)
    {
        line(400, i * gap, 400 + ary2[i], i * gap, RGB(255, 165, 0));
    }
    sort_bubble2(ary2);
    task_exit(0);
}

void sort_bubble1(int ary[])
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
                nanosleep(0, 500000000);
                temp = ary[j];
                ary[j] = ary[j - 1];
                ary[j - 1] = temp;
                line(0, (j - 1) * gap, ary[j - 1], (j - 1) * gap, RGB(128, 0, 128));
                line(0, j * gap, ary[j], j * gap, RGB(128, 0, 128));
                nanosleep(0, 500000000);
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
                line(400, (j - 1) * gap, 400 + ary[j - 1], (j - 1) * gap, RGB(0, 0, 0));
                nanosleep(0, 500000000);
                temp = ary[j];
                ary[j] = ary[j - 1];
                ary[j - 1] = temp;
                line(400, (j - 1) * gap, 400 + ary[j - 1], (j - 1) * gap, RGB(255, 165, 0));
                line(400, j * gap, 400 + ary[j], j * gap, RGB(255, 165, 0));
                nanosleep(0, 500000000);
            }
        }
    }
}