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

extern void *tlsf_create_with_pool(void *mem, size_t bytes);
extern void *g_heap;

#define N 7           // 需要生成的列表数量和线程数量
#define LIST_SIZE 300 // 每个列表的大小
#define GAP 2         // 每个条形的间隔
void sort_thread_1(void *arg)
{
    printf("Thread 1 started.\n");
    int *list = (int *)arg;
    int size = LIST_SIZE; //  LIST_SIZE 是列表的大小

    // 冒泡排序算法
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        { // 从小到大排序
            if (list[j] > list[j + 1])
            {
                // 清除之前的绘图痕迹（黑色线段）
                line(0, j * GAP, list[j], j * GAP, RGB(0, 0, 0));
                line(0, (j + 1) * GAP, list[j + 1], (j + 1) * GAP, RGB(0, 0, 0));
                // 交换 list[j] 和 list[j + 1]
                int temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;

                // 绘制交换后的数据（红色线段）
                line(0, j * GAP, list[j], j * GAP, RGB(255, 0, 0));
                line(0, (j + 1) * GAP, list[j + 1], (j + 1) * GAP, RGB(255, 0, 0));
            }
        }
    }

    printf("Thread 1 finished.\n");
    task_exit(0);
}
void sort_thread_2(void *arg)
{
    printf("Thread 2 started.\n");
    int *list = (int *)arg;
    int size = LIST_SIZE; //  LIST_SIZE 是列表的大小

    // 选择排序算法
    for (int i = 0; i < size - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (list[j] < list[min_index])
            {
                min_index = j;
            }
        }
        // 将找到的最小元素交换到已排序部分的末尾
        if (min_index != i)
        {
            int temp = list[i];
            list[i] = list[min_index];
            list[min_index] = temp;
        }
    }
    printf("Thread 2 finished.\n");
    task_exit(0);
}
void sort_thread_3(void *arg)
{
    printf("Thread 3 started.\n");

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
            list[j + 1] = list[j];
            j = j - 1;
        }
        list[j + 1] = key;
    }
    printf("Thread 3 finished.\n");

    task_exit(0);

} // 快速排序的辅助函数
int partition(int *list, int low, int high)
{
    int pivot = list[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (list[j] < pivot)
        {
            i++;
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    int temp = list[i + 1];
    list[i + 1] = list[high];
    list[high] = temp;
    return (i + 1);
}

// 实际的快速排序函数
void quickSort(int *list, int low, int high)
{
    if (low < high)
    {
        int pi = partition(list, low, high);

        quickSort(list, low, pi - 1);
        quickSort(list, pi + 1, high);
    }
}

void sort_thread_4(void *arg)
{
    printf("Thread 4 started.\n");

    int *list = (int *)arg;
    int size = LIST_SIZE; // 假设 LIST_SIZE 是列表的大小

    // 快速排序算法
    quickSort(list, 0, size - 1);
    printf("Thread 4 finished.\n");

    task_exit(0);
}

// 归并排序的辅助函数
void merge(int *list, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = list[left + i];
    for (j = 0; j < n2; j++)
        R[j] = list[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            list[k] = L[i];
            i++;
        }
        else
        {
            list[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        list[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        list[k] = R[j];
        j++;
        k++;
    }
}

// 实际的归并排序函数
void mergeSort(int *list, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);

        merge(list, left, mid, right);
    }
}

void sort_thread_5(void *arg)
{
    printf("Thread 5 started.\n");

    int *list = (int *)arg;
    int size = LIST_SIZE; // 假设 LIST_SIZE 是列表的大小

    // 归并排序算法
    mergeSort(list, 0, size - 1);
    printf("Thread 5 finished.\n");

    task_exit(0);
}
// 堆排序的辅助函数
void heapify(int *list, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && list[left] > list[largest])
        largest = left;

    if (right < n && list[right] > list[largest])
        largest = right;

    if (largest != i)
    {
        int swap = list[i];
        list[i] = list[largest];
        list[largest] = swap;

        heapify(list, n, largest);
    }
}

// 实际的堆排序函数
void heapSort(int *list, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(list, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        int temp = list[0];
        list[0] = list[i];
        list[i] = temp;

        heapify(list, i, 0);
    }
}

void sort_thread_6(void *arg)
{
    printf("Thread 6 started.\n");

    int *list = (int *)arg;
    int size = LIST_SIZE; // 假设 LIST_SIZE 是列表的大小

    // 堆排序算法
    heapSort(list, size);
    printf("Thread 6 finished.\n");

    task_exit(0);
}
// 实际的希尔排序函数
void shellSort(int *list, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = list[i];
            int j;
            for (j = i; j >= gap && list[j - gap] > temp; j -= gap)
            {
                list[j] = list[j - gap];
            }
            list[j] = temp;
        }
    }
}

void sort_thread_7(void *arg)
{
    printf("Thread 7 started.\n");
    int *list = (int *)arg;
    int size = LIST_SIZE; // 假设 LIST_SIZE 是列表的大小

    // 希尔排序算法
    shellSort(list, size);
    printf("Thread 7 finished.\n");

    task_exit(0);
}
void (*sort_functions[N])(void *) = {sort_thread_1, sort_thread_2, sort_thread_3, sort_thread_4, sort_thread_5, sort_thread_6, sort_thread_7};

void create_sort_threads(int thread_index, int *list, int x_start)
{
    int threads[thread_index];             // 存储线程ID的数组
    unsigned char *stacks[thread_index];   // 存储线程栈的数组
    unsigned int stack_size = 1024 * 1024; // 定义每个线程栈的大小

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

    line(region_width, 0, region_width, y_res, RGB(255, 0, 0));
    line(region_width * 2, 0, region_width * 2, y_res, RGB(255, 0, 0));
    line(region_width * 3, 0, region_width * 3, y_res, RGB(255, 0, 0));
    line(region_width * 4, 0, region_width * 4, y_res, RGB(255, 0, 0));
    line(region_width * 5, 0, region_width * 5, y_res, RGB(255, 0, 0));
    line(region_width * 6, 0, region_width * 6, y_res, RGB(255, 0, 0));

    // 生成一个随机列表
    int *random_list = generate_random_list(LIST_SIZE, region_width);

    // 创建并启动排序线程
    for (int i = 0; i < N; i++)
    {
        // 计算当前区域的起始位置
        int x_start = i * region_width;

        // 创建排序线程，传递相同的随机列表
        create_sort_threads(i, random_list, x_start);
    }

    // 退出图形模式
    // exit_graphic();

    while (1)
        ;
    task_exit(0);
}