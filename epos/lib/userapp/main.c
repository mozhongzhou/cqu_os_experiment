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

#define NZERO 20
#define PRI_USER_MIN 0
#define PRI_USER_MAX 127
// 间隔值：用于描绘nice实体
#define emp2 2
#define N 200

void tsk_1(void *pv);
void tsk_2(void *pv);
void tsk_3(void *pv);
void sort_bubble1(int ary[]);
void sort_bubble2(int ary[]);

int ary1[N], ary2[N];
int tid1, tid2;
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
    for (int i = 0, temp; i < N; i++)
    {
        temp = rand() % 400;
        ary1[i] = temp;
        ary2[i] = temp;
    }

    int mode = 0x143;
    init_graphic(mode);
    line(400, 0, 400, 600, RGB(255, 0, 0)); // 屏幕中间一根红线分隔开
    // Apply for the stack
    unsigned int stack_size = 1024 * 1024;
    unsigned char *stack_foo1 = (unsigned char *)malloc(stack_size);
    unsigned char *stack_foo2 = (unsigned char *)malloc(stack_size);
    unsigned char *stack_foo3 = (unsigned char *)malloc(stack_size);

    // Creat the thread
    int tid_1, tid_2, tid_3;

    tid_1 = task_create(stack_foo1 + stack_size, &tsk_1, (void *)0);
    setpriority(tid_1, 15);
    tid_2 = task_create(stack_foo2 + stack_size, &tsk_2, (void *)0);
    setpriority(tid_2, 15);
    tid_3 = task_create(stack_foo3 + stack_size, &tsk_3, (void *)0);
    setpriority(tid_3, 0);

    tid1 = tid_1;
    tid2 = tid_2;
    // wait for the thread to exit
    task_wait(tid_1, NULL);
    task_wait(tid_2, NULL);
    task_wait(tid_3, NULL);

    // Free the stack
    free(stack_foo1);
    free(stack_foo2);
    free(stack_foo3);
    while (1)
        ;
    task_exit(0);
}

void tsk_1(void *pv)
{

    int gap = 2;
    for (int i = 0; i < N; i++)
    {
        line(0, i * gap, ary1[i], i * gap, RGB(128, 0, 128));
    }
    sort_bubble1(ary1);
    task_exit(0);
}
void tsk_2(void *pv)
{

    int gap = 2;
    for (int i = 0; i < N; i++)
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

    for (i = 1; i < N; i++)
    {
        for (j = i; j > 0; j--)
        {
            if (ary[j] < ary[j - 1])
            {
                line(0, (j - 1) * gap, ary[j - 1], (j - 1) * gap, RGB(0, 0, 0));
                temp = ary[j];
                ary[j] = ary[j - 1];
                ary[j - 1] = temp;
                line(0, (j - 1) * gap, ary[j - 1], (j - 1) * gap, RGB(128, 0, 128));
                line(0, j * gap, ary[j], j * gap, RGB(128, 0, 128));
                struct timespec sleepTime;
                sleepTime.tv_sec = 0;          // seconds
                sleepTime.tv_nsec = 100000000; // nanoseconds
                nanosleep(&sleepTime, NULL);
            }
        }
    }
}
void sort_bubble2(int ary[])
{
    int i, j, temp = 0;
    int gap = 2;

    for (i = 1; i < N; i++)
    {
        for (j = i; j > 0; j--)
        {
            if (ary[j] < ary[j - 1])
            {
                line(400, (j - 1) * gap, 400 + ary[j - 1], (j - 1) * gap, RGB(0, 0, 0));
                temp = ary[j];
                ary[j] = ary[j - 1];
                ary[j - 1] = temp;
                line(400, (j - 1) * gap, 400 + ary[j - 1], (j - 1) * gap, RGB(255, 165, 0));
                line(400, j * gap, 400 + ary[j], j * gap, RGB(255, 165, 0));
                struct timespec sleepTime;
                sleepTime.tv_sec = 0;          // seconds
                sleepTime.tv_nsec = 100000000; // nanoseconds
                nanosleep(&sleepTime, NULL);
            }
        }
    }
}
void tsk_3(void *pv)
{
    /*
    事实上这个getpriority和setpriority是获取、改变的nice值，nice值越小优先级越高。
    然而为了可视化，需要做一个运算，具体运算体现在setpriority函数中。
    */
    int i;

    int nice1 = getpriority(tid1); // 获取线程优先级
    int nice2 = getpriority(tid2);

    for (i = 0; i <= nice1; i++) // 画出nice的实体
        line(g_graphic_dev.XResolution / 2 - i * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 - 25,
             g_graphic_dev.XResolution / 2 - i * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(128, 0, 128));
    for (i = 0; i <= nice2; i++)
        line(g_graphic_dev.XResolution / 2 + i * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 - 25,
             g_graphic_dev.XResolution / 2 + i * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(255, 165, 0));

    do
    {
        int key = getchar();
        if (key == 0x4800) // up 提高任务1的优先度
        {
            nice1 = nice1 + 1;
            if (nice1 > PRI_USER_MAX)
                nice1 = PRI_USER_MAX;
            setpriority(tid1, PRI_USER_MAX - nice1);
            line(g_graphic_dev.XResolution / 2 - nice1 * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 - 25,
                 g_graphic_dev.XResolution / 2 - nice1 * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(128, 0, 128));
        }
        else if (key == 0x5000) // down 降低任务1的优先度
        {
            line(g_graphic_dev.XResolution / 2 - nice1 * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 - 25,
                 g_graphic_dev.XResolution / 2 - nice1 * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(0, 0, 0)); // 消失涂黑
            nice1 = nice1 - 1;
            if (nice1 < PRI_USER_MIN)
                nice1 = PRI_USER_MIN;
            setpriority(tid1, PRI_USER_MAX - nice1);
        }
        if (key == 0x4D00) // right 提高任务2的优先度
        {
            nice2 = nice2 + 1;
            if (nice2 > PRI_USER_MAX)
                nice2 = PRI_USER_MAX;
            setpriority(tid2, PRI_USER_MAX - nice2);
            line(g_graphic_dev.XResolution / 2 + nice2 * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 - 25,
                 g_graphic_dev.XResolution / 2 + nice2 * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(255, 165, 0));
        }
        else if (key == 0x4B00) // left 降低任务2的优先度
        {
            line(g_graphic_dev.XResolution / 2 + nice2 * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 - 25,
                 g_graphic_dev.XResolution / 2 + nice2 * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(0, 0, 0));
            nice2 = nice2 - 1;
            if (nice2 < PRI_USER_MIN)
                nice2 = PRI_USER_MIN;
            setpriority(tid2, PRI_USER_MAX - nice2);
        }
    } while (1); // 重复获取键盘输入

    task_exit(0);
}