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
#include "list_utils.h"
#include <time.h>
extern void *tlsf_create_with_pool(void *mem, size_t bytes);
extern void *g_heap;

#define N 5           // 需要生成的列表数量和线程数量
#define LIST_SIZE 200 // 每个列表的大小
#define GAP 3         // 每个条形的间隔

void sort_thread_1(void *arg)
{
    struct timespec ts;
    ts.tv_sec = 0;          // 秒
    ts.tv_nsec = 10000000L; // 纳秒
    // 获取屏幕分辨率
    int x_res = g_graphic_dev.XResolution;
    // 计算每个区域的宽度
    int region_width = x_res / N * 0;

    int *list = (int *)arg;
    int size = LIST_SIZE; //  LIST_SIZE 是列表的大小

    int i, j, min_idx, temp;

    // 选择排序算法
    // 遍历所有数组元素
    for (i = 0; i < size - 1; i++)
    {
        // 找到剩余部分的最小元素
        min_idx = i;
        for (j = i + 1; j < size; j++)
            if (list[j] < list[min_idx])
                min_idx = j;

        // 将找到的最小元素交换到已排序部分的末尾 从前往后增大
        temp = list[min_idx]; // 把第i和第min_idx个元素交换
        line(region_width, i * GAP, region_width + list[i], i * GAP, RGB(0, 0, 0));

        line(region_width, min_idx * GAP, region_width + list[min_idx], min_idx * GAP, RGB(0, 0, 0));
        nanosleep(&ts, NULL);
        list[min_idx] = list[i];
        list[i] = temp;

        line(region_width, i * GAP, region_width + list[i], i * GAP, RGB(100, 149, 237));
        line(region_width, min_idx * GAP, region_width + list[min_idx], min_idx * GAP, RGB(100, 149, 237));
    }

    task_exit(0);
}
void sort_thread_2(void *arg)
{
    struct timespec ts;
    ts.tv_sec = 0;           // 秒
    ts.tv_nsec = 200000000L; // 纳秒

    // 获取屏幕分辨率
    int x_res = g_graphic_dev.XResolution;
    // 计算每个区域的宽度
    int region_width = x_res / N * 1;

    int *list = (int *)arg;
    int size = LIST_SIZE; // 假设 LIST_SIZE 是列表的大小

    // 插入排序算法
    for (int i = 1; i < size; i++)
    {
        int key = list[i];
        int j = i - 1;

        // 将大于 key 的元素向后移动一位
        while (j >= 0 && list[j] > key)
        {
            line(region_width, (j + 1) * GAP, region_width + list[j + 1], (j + 1) * GAP, RGB(0, 0, 0));
            line(region_width, j * GAP, region_width + list[j], j * GAP, RGB(0, 0, 0));

            list[j + 1] = list[j];
            line(region_width, (j + 1) * GAP, region_width + list[j + 1], (j + 1) * GAP, RGB(106, 90, 205));
            nanosleep(&ts, NULL);
            j--;
        }
        list[j + 1] = key;
        line(region_width, (j + 1) * GAP, region_width + list[j + 1], (j + 1) * GAP, RGB(106, 90, 205));
        nanosleep(&ts, NULL);
    }

    task_exit(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////

void sort_thread_3(void *arg)
{

    struct timespec ts;
    ts.tv_sec = 0;        // 秒
    ts.tv_nsec = 900000L; // 纳秒
    // 获取屏幕分辨率
    int x_res = g_graphic_dev.XResolution;
    // 计算每个区域的宽度
    int region_width = x_res / N * 2;
    int *list = (int *)arg;
    int size = LIST_SIZE;
    // 冒泡排序
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (list[j] > list[j + 1])
            {
                // 画线：清除之前的绘图痕迹（黑色线段）
                line(region_width, j * GAP, region_width + list[j], j * GAP, RGB(0, 0, 0));
                line(region_width, (j + 1) * GAP, region_width + list[j + 1], (j + 1) * GAP, RGB(0, 0, 0));
                int temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;

                // 绘制交换后的数据（红色线段）
                line(region_width, j * GAP, region_width + list[j], j * GAP, RGB(173, 255, 47));
                line(region_width, (j + 1) * GAP, region_width + list[j + 1], (j + 1) * GAP, RGB(173, 255, 47));
                nanosleep(&ts, NULL);
            }
        }
    }

    task_exit(0);
}
//////////////////////////////////////////////////////////////////////////////
void merge(int *arr, int l, int m, int r)
{
    struct timespec ts;
    ts.tv_sec = 0;          // 秒
    ts.tv_nsec = 10000000L; // 纳秒

    // 获取屏幕分辨率
    int x_res = g_graphic_dev.XResolution;
    // 计算每个区域的宽度
    int region_width = x_res / N * 3;
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        // 画线：清除之前的绘图痕迹（黑色线段）
        line(region_width, k * GAP, region_width + arr[k], k * GAP, RGB(0, 0, 0));

        // 绘制当前值（红色线段）
        line(region_width, k * GAP, region_width + arr[k], k * GAP, RGB(238, 173, 14));
        nanosleep(&ts, NULL);
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
void sort_thread_4(void *arg)
{

    int *list = (int *)arg;
    int size = LIST_SIZE; // 假设 LIST_SIZE 是列表的大小
    mergeSort(list, 0, size - 1);
    task_exit(0);
}

// 实际的希尔排序函数
void shellSort(int *list, int n)
{
    struct timespec ts;
    ts.tv_sec = 0;          // 秒
    ts.tv_nsec = 10000000L; // 纳秒

    // 获取屏幕分辨率
    int x_res = g_graphic_dev.XResolution;
    // 计算每个区域的宽度
    int region_width = x_res / N * 4;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = list[i];
            int j;
            for (j = i; j >= gap && list[j - gap] > temp; j -= gap)
            {
                line(region_width, j * GAP, region_width + list[j], j * GAP, RGB(0, 0, 0));

                line(region_width, (j - gap) * GAP, region_width + list[j - gap], (j - gap) * GAP, RGB(0, 0, 0));

                list[j] = list[j - gap];

                // 描出新的线
                line(region_width, j * GAP, region_width + list[j], j * GAP, RGB(255, 48, 48));
            }
            list[j] = temp;

            line(region_width, j * GAP, region_width + list[j], j * GAP, RGB(255, 48, 48));
            nanosleep(&ts, NULL);
        }
    }
}

void sort_thread_5(void *arg)
{

    int *list = (int *)arg;
    int size = LIST_SIZE; // 假设 LIST_SIZE 是列表的大小

    // 希尔排序算法
    shellSort(list, size);

    task_exit(0);
}
void (*sort_functions[N])(void *) = {sort_thread_1, sort_thread_2, sort_thread_3, sort_thread_4, sort_thread_5};

void create_sort_threads(int thread_index, int *list)
{
    int threads[thread_index];                 // 存储线程ID的数组
    unsigned char *stacks[thread_index];       // 存储线程栈的数组
    unsigned int stack_size = 2 * 1024 * 1024; // 定义每个线程栈的大小

    // 创建和启动排序线程
    for (int i = 0; i < thread_index; i++)
    {
        // 分配线程栈空间
        stacks[i] = (unsigned char *)malloc(stack_size);
        // 创建排序线程
        threads[i] = task_create(stacks[i] + stack_size, sort_functions[i], list);
    }

    // 等待所有线程完成
    for (int i = 0; i < thread_index; i++)
    {
        int exit_code;
        task_wait(threads[i], &exit_code);
        free(stacks[i]); // 释放线程栈的内存
    }
}

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

    // 初始化图形模式
    init_graphic(0x143);
    // 获取屏幕分辨率
    int x_res = g_graphic_dev.XResolution;
    int y_res = g_graphic_dev.YResolution;
    // 计算每个区域的宽度
    int region_width = x_res / N;
    line(region_width, 0, region_width, y_res, RGB(100, 100, 100));
    line(region_width * 2, 0, region_width * 2, y_res, RGB(100, 100, 100));
    line(region_width * 3, 0, region_width * 3, y_res, RGB(100, 100, 100));
    line(region_width * 4, 0, region_width * 4, y_res, RGB(100, 100, 100));
    // 生成一个随机列表
    int *random_list = generate_random_list(LIST_SIZE, region_width);
    create_sort_threads(N, random_list);
    // 退出图形模式
    // exit_graphic();
    while (1)
        ;
    task_exit(0);
}