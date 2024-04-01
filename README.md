# 操作系统第二次实验报告

20220815 2024/3/22

切换到分支 experiment2

## 任务记录

### 1、分析代码架构和提供的接口

```cpp
//创建
int task_create(void *tos, void (*func)(void *pv), void *pv)
tos ：用户栈的栈顶指针
func ：线程函数
pv ：传递给线程函数func的参数
返回值 ：大于0，则表示新创建线程之ID

//退出
int task_exit(int code_exit);
code_exit ：线程的退出代码


//获取线程自己的ID
int task_getid();


//等待线程退出
int task_wait(int tid, int *pcode_exit);
tid ：要等待线程之ID
pcode_exit ：如果非NULL，用于保存线程tid的退出代码


//以上代码在userapp/include/syscall.h
//观察epos/kernel/task.c，观测到内核类似的接口
```

![image-20240322090757004](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240322090757004.png)

### 2、第一次线程创建测试

epos/userapp/main.c

```cpp
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

void tsk_foo(void *pv)
{
    printf("This is task foo with tid=%d\r\n", task_getid());
    task_exit(0); // 不能直接 return，必须调用 task_exit
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
    printf("task #%d: I'm the first user task(pv=0x%08x)!\r\n",
           task_getid(), pv);
    // 创建新的线程
    unsigned char *stack_foo;
    unsigned int stack_size = 1024 * 1024;
    stack_foo = (unsigned char *)malloc(stack_size);
    int tid_foo;
    tid_foo = task_create(stack_foo + stack_size, &tsk_foo, (void *)0);
    while (1)
        ;
    task_exit(0);
}
```

![image-20240322093740505](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240322093740505.png)

用 ctrl+shift+b 快速编译启动

注意架构更改后 要在 Makefile 处增添链接文件

> COBJS= vm86call.o graphics.o main.o list_utils.o

### 3、创建多线程

epos/userapp/main.c

我准备写五个排序算法，用五个线程，所以开五个 thread 和 stack 使其一一对应

```cpp
void sort_thread_1(void *arg)
{
}
void sort_thread_2(void *arg)
{
}
void sort_thread_3(void *arg)
{
}
void sort_thread_4(void *arg)
{
}
void sort_thread_5(void *arg)
{
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
```

### 4、编写排序算法

**选择排序 、 插入排序**

**都是把前面当作已排好、后面当作未排序**，**选择**是挑选未排序里**最小**的元素从前往后放到已排序；插入是将**未排序**里的元素依次放到**已排序**的合适位置

**冒泡排序**

从前往后依次比较相邻元素，并调整为正确次序

**归并排序**

分治思想，把数列分成几个部分，对每个部分排序好后再合成一个

希尔排序

插入排序的改良版 缩小增量排序

```cpp
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

        list[min_idx] = list[i];
        list[i] = temp;

        line(region_width, i * GAP, region_width + list[i], i * GAP, RGB(100, 149, 237));
        line(region_width, min_idx * GAP, region_width + list[min_idx], min_idx * GAP, RGB(100, 149, 237));
        nanosleep(&ts, NULL);
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
    ts.tv_sec = 0;         // 秒
    ts.tv_nsec = 9000000L; // 纳秒
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
```

### 5、随机生成 LIST

```cpp
// list_utils.c
#include "list_utils.h"
#include "graphics.h"
#include <time.h>
int *generate_random_list(int size, int region_width)
{
    int *list = (int *)malloc(size * sizeof(int));

    // 使用当前时间作为随机种子
    srand(time(NULL));

    // 填充随机数据
    for (int i = 0; i < size; i++)
    {
        list[i] = rand() % 150;
    }
    return list;
}

```

### 6、运用提供的接口画图

#### 查看分辨率的接口

```cpp
  int x_res = g_graphic_dev.XResolution;

  *//* *计算每个区域的宽度*

  int region_width = x_res / **N** * 0;
```

#### 画图的函数

```cpp
void line(int x1,int y1,int x2,int y2, COLORREF cr)
{
    int d; /* Decision variable */
    int dx,dy; /* Dx and Dy values for the line */
    int Eincr, NEincr;/* Decision variable increments */
    int yincr;/* Increment for y values */
    int t; /* Counters etc. */

#define ABS(a) ((a) >= 0 ? (a) : -(a))

    dx = ABS(x2 - x1);
    dy = ABS(y2 - y1);
    if (dy <= dx)
    {
        /* We have a line with a slope between -1 and 1
         *
         * Ensure that we are always scan converting the line from left to
         * right to ensure that we produce the same line from P1 to P0 as the
         * line from P0 to P1.
         */
        if (x2 < x1)
        {
            t=x2;x2=x1;x1=t; /*SwapXcoordinates */
            t=y2;y2=y1;y1=t; /*SwapYcoordinates */
        }
        if (y2 > y1)
            yincr = 1;
        else
            yincr = -1;
        d = 2*dy - dx;/* Initial decision variable value */
        Eincr = 2*dy;/* Increment to move to E pixel */
        NEincr = 2*(dy - dx);/* Increment to move to NE pixel */
        setPixel(x1,y1,cr); /* Draw the first point at (x1,y1) */

        /* Incrementally determine the positions of the remaining pixels */
        for (x1++; x1 <= x2; x1++)
        {
            if (d < 0)
                d += Eincr; /* Choose the Eastern Pixel */
            else
            {
                d += NEincr; /* Choose the North Eastern Pixel */
                y1 += yincr; /* (or SE pixel for dx/dy < 0!) */
            }
            setPixel(x1,y1,cr); /* Draw the point */
        }
    }
    else
    {
        /* We have a line with a slope between -1 and 1 (ie: includes
         * vertical lines). We must swap our x and y coordinates for this. *
         * Ensure that we are always scan converting the line from left to
         * right to ensure that we produce the same line from P1 to P0 as the
         * line from P0 to P1.
         */
        if (y2 < y1)
        {
            t=x2;x2=x1;x1=t; /*SwapXcoordinates */
            t=y2;y2=y1;y1=t; /*SwapYcoordinates */
        }
        if (x2 > x1)
            yincr = 1;
        else
            yincr = -1;
        d = 2*dx - dy;/* Initial decision variable value */
        Eincr = 2*dx;/* Increment to move to E pixel */
        NEincr = 2*(dx - dy);/* Increment to move to NE pixel */
        setPixel(x1,y1,cr); /* Draw the first point at (x1,y1) */

        /* Incrementally determine the positions of the remaining pixels */
        for (y1++; y1 <= y2; y1++)
        {
            if (d < 0)
                d += Eincr; /* Choose the Eastern Pixel */
            else
            {
                d += NEincr; /* Choose the North Eastern Pixel */
                x1 += yincr; /* (or SE pixel for dx/dy < 0!) */
            }
            setPixel(x1, y1, cr);
        }
    }
}

```

#### 自带的时延函数

epos/userapp/include/syscall.h

```cpp
unsigned sleep(unsigned seconds);
int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
```

### 7、把以上内容综合在一起

## 经验记录

1、**经验太多 太杂，下次应该边做 proj 边写记录，不然隔久了容易忘**

2、最大的问题：在多个线程中调用**时延函数**可能会导致**退出任务时**影响到其他线程

具体表现在：例如线程 1 中调用 nanosleep 会导致线程 2 作图出现奇怪的情况，例如下图

如何避免？ 改变时延（无法根除）我也不知道如何彻底修正。

可能与时延函数有关 可能与退出任务的逻辑有关

---

以下是动态排序过程

![image-20240401104233942](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240401104233942.png)

以下是排序好后的图（图像上存在误差，但实际 LIST 数据是正确的）

![image-20240401104205018](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240401104205018.png)

---

3、在做一个 proj 的时候，最好从简入深，用特定示例理解代码整体架构以及运转流程，如果可以的话，进行断点调试，看看代码流转过程

## 代码理解

### 1、生成随机列表

1. `#include "list_utils.h"` 和 `#include "graphics.h"`：这两行代码包含了相关的头文件，以便在函数中使用相应的函数和数据结构。
2. `int *generate_random_list(int size, int region_width)`：这是 `generate_random_list` 函数的声明，它接受两个参数：`size` 表示要生成的随机整数列表的大小，`region_width` 表示区域的宽度，但在该函数中并没有使用这个参数。
3. `int *list = (int *)malloc(size * sizeof(int));`：这一行代码动态分配了一个大小为 `size` 的整型数组，并将其地址赋给指针 `list`。这里使用了 `malloc` 函数来分配内存。
4. `srand(time(NULL));`：该行代码设置随机数种子，以确保每次运行程序时生成的随机数序列是不同的。`time(NULL)` 返回当前时间的秒数，作为随机数种子。
5. `for (int i = 0; i < size; i++)`：这是一个 `for` 循环，用于迭代生成随机数列表的每个元素。
6. `list[i] = rand() % 150;`：这一行代码生成一个范围在 0 到 149 之间的随机整数，并将其赋值给列表中的第 `i` 个元素。
7. `return list;`：最后，该函数返回指向生成的随机整数列表的指针 `list`。

这段代码主要实现了一个简单的功能：根据指定的大小生成随机整数列表，并返回该列表的指针。通过动态内存分配，可以确保生成的列表在函数执行完毕后仍然存在，因此可以在调用函数的其他地方使用这个列表。

### 2、线程创建

这些函数的定义通常在操作系统的内核中，或者是操作系统提供的系统库中。这些函数提供了对操作系统的各种功能的访问，例如任务管理、内存管理、时间管理等。

具体来说：

- `task_exit`, `task_create`, `task_getid`, `task_yield`, `task_wait` 等函数通常用于任务管理，包括任务的创建、退出、等待和切换等操作。
- `reboot` 函数用于系统的重启。
- `mmap` 和 `munmap` 函数用于内存映射。
- `sleep` 和 `nanosleep` 函数用于线程的睡眠。
- `time` 函数用于获取当前时间。
- `beep` 函数用于发出蜂鸣声。
- `putchar` 和 `getchar` 函数用于字符的输入输出。
- `vm86` 函数用于执行虚拟 8086 模式下的程序。

这些函数的具体实现通常在操作系统内核中，以及提供给用户空间的系统库中。实现方式取决于操作系统的设计和实现方式。

### 3、画图

这段代码是关于在图形模式下绘制直线的实现，主要包括以下几个部分：

1. 宏定义：定义了一些辅助宏，如 `MAJOR`、`MINOR`、`LOWORD`、`HIWORD` 等，用于提取版本号、低位、高位等信息。
2. 结构体定义：定义了 `VBEInfoBlock` 和 `ModeInfoBlock` 结构体，用于存储 VBE 信息和显示模式信息。
3. 函数实现：实现了一系列函数，包括获取 VBE 信息、获取模式信息、获取当前 VBE 模式、设置 VBE 模式、切换内存分段等。
4. 绘制直线函数：实现了 `line` 函数，用于在图形模式下绘制直线。该函数采用了 Bresenham 算法，根据起点和终点坐标，利用数值微分的思想来逐步计算出直线上的像素点，并调用 `setPixel` 函数来设置像素点的颜色。
5. 其他函数：包括 `list_graphic_modes` 和 `init_graphic` 等，用于列出支持的图形模式和初始化图形模式。

该段代码主要用于操作 VBE（VESA BIOS Extensions），在支持 VBE 的系统中实现图形模式的初始化和绘制操作。

### 4、一些编译内容

```json
User
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Run start.bat",
            "type": "shell",
            "command": "${workspaceFolder}\\start.bat",
            "problemMatcher": [],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

这段 JSON 代码是一个任务配置文件，用于配置一个名为 "Run start.bat" 的任务，该任务的作用是运行名为 "start.bat" 的批处理文件。

具体解释如下：

- `"version": "2.0.0"`：指定了该配置文件的版本号，这里是 2.0.0 版本。
- `"tasks"`：指定了一个任务列表，该列表包含了一个任务对象。
- `"label": "Run start.bat"`：任务的标签，用于在用户界面中显示。
- `"type": "shell"`：任务的类型，这里是一个 shell 命令。
- `"command": "${workspaceFolder}\\start.bat"`：指定了要执行的命令或脚本，`${workspaceFolder}` 是一个变量，代表当前工作空间的路径，这里使用双反斜杠是因为在 JSON 中需要转义反斜杠。
- `"problemMatcher": []`：指定了问题匹配器，这里为空数组，表示不使用任何问题匹配器。
- `"group"`：指定了任务的分组信息。
  - `"kind": "build"`：表示该任务属于构建任务。
  - `"isDefault": true`：表示该任务是默认任务，在执行任务时将默认选择该任务。

这段配置文件的作用是在 Visual Studio Code 中配置一个默认的构建任务，当用户执行构建操作时，将会自动运行名为 "start.bat" 的批处理文件。

有了这个可以快捷编译调试 （windows 在 vscode 里快捷键是 ctrl+shift+b）

### 5、两个 Makefile 理解

**第一个 epos/Makefile**

1. `include Makefile.inc`：包含了名为 `Makefile.inc` 的外部文件，这个文件可能包含了一些变量或规则的定义，用于在当前 Makefile 中重复使用。
2. `all: hd.img`：定义了一个名为 `all` 的伪目标，它依赖于 `hd.img`。这表示当执行 `make all` 命令时，会自动构建 `hd.img`。
3. `MODE = run`：定义了一个名为 `MODE` 的变量，并给它赋值为 `run`。该变量可能用于控制编译或运行时的模式。
4. `SUBDIRS = kernel userapp`：定义了一个名为 `SUBDIRS` 的变量，包含了需要构建的子目录列表。
5. `subdirs: $(SUBDIRS)`：定义了一个名为 `subdirs` 的伪目标，它依赖于 `$(SUBDIRS)` 中列出的子目录。这表示执行 `make subdirs` 时会依次进入这些子目录并执行相应的操作。
6. `hd.img: subdirs`：定义了一个名为 `hd.img` 的目标，它依赖于 `subdirs` 目标，表示在构建 `hd.img` 之前需要先执行 `subdirs` 目标中的操作。
7. 该文件中还包含了针对不同操作系统（Windows、Linux、Darwin）的条件判断，以及针对不同命令行工具（`qemu`、`bochs`、`VBoxManage`）的任务配置。
8. `qemu`、`qemudbg`、`bochs`、`bochsdbg`、`vbox` 等任务用于运行或调试操作系统。
9. `tags` 任务用于生成代码标签。
10. `clean` 任务用于清理生成的文件。
11. `submit` 任务用于提交代码至指定的服务器，并有一系列的输入验证和提交流程。

整体上，这个 Makefile 文件用于管理整个操作系统项目的构建、运行、调试和提交等任务。

**第二个 epos/userapp/Makefile**

1. `include ../Makefile.inc`：包含了一个名为 `Makefile.inc` 的外部文件，该文件可能包含了一些通用的配置或规则。
2. `PROG= a`：定义了一个名为 `PROG` 的变量，用于指定程序的名称为 `a`。
3. `all: make.dep run`：定义了一个名为 `all` 的伪目标，它依赖于 `make.dep` 和 `run`，表示执行 `make all` 时会先生成依赖关系文件 `make.dep`，然后运行 `run` 目标。
4. 定义了一些编译器选项：
   - `CPPFLAGS` 包含了一些预处理器选项，如 `-nostdlib` 表示不使用标准库， `-I` 表示添加头文件搜索路径。
   - `ASFLAGS` 包含了汇编器选项。
   - `CFLAGS` 包含了 C 编译器选项，如指定目标架构、警告选项等。
5. `LDFLAGS` 包含了链接器选项，如指定目标架构、不使用标准库等。
6. 定义了一些源文件对象文件的依赖关系：
   - `COBJS` 包含了 C 源文件编译生成的对象文件列表。
   - `OBJS` 包含了所有的对象文件列表，包括 `COBJS` 中的对象文件以及一些其他的对象文件。
7. `$(PROG).out: $(OBJS)`：定义了生成程序的规则，它依赖于 `$(OBJS)` 中列出的所有对象文件，表示执行链接器将这些对象文件链接成可执行文件。
8. `make.dep: *.c *.h`：定义了生成依赖关系文件的规则，它依赖于当前目录下的所有 `.c` 和 `.h` 文件。
9. `debug: $(PROG).out` 和 `run: $(PROG).out`：定义了两个伪目标，分别用于调试和运行程序。它们都依赖于生成程序的规则。
10. `clean`：定义了清理目标，用于删除生成的对象文件、可执行文件以及依赖关系文件。
11. `-include make.dep`：包含了依赖关系文件 `make.dep`，如果该文件不存在也不会报错。

整体上，这个 Makefile 文件用于编译、链接和运行程序，并且包含了调试和清理的相关规则。

## 创新部分

### **1、多线程排序算法的实现**：

1. **创建多个排序线程**：
   - 定义了多个排序函数，每个函数对应一个排序算法，例如`sort_thread_1`到`sort_thread_5`。
   - 每个排序函数都接受一个指向待排序列表的指针作为参数，并在函数内部执行特定的排序算法。
2. **线程函数实现排序算法**：
   - 每个排序函数内部实现了一个具体的排序算法，如选择排序、插入排序、冒泡排序、归并排序和希尔排序。
   - 例如，在`sort_thread_1`中， 使用了选择排序算法，通过遍历列表并选择最小的元素进行交换来排序。
3. **线程间同步和协作**：
   - 在每个排序线程中， 使用了`nanosleep`函数来进行线程的睡眠，以模拟排序过程中的延迟效果，使得排序过程可以以一定的速度展示在图形界面上。
   - 在每次排序操作后， 通过绘制不同颜色的线段来清除之前的绘图痕迹并绘制当前的排序结果，以在图形界面上展示排序过程。
4. **创建和启动线程**：
   - 在`create_sort_threads`函数中， 动态地创建了多个线程，并为每个线程分配了一块独立的内存栈空间。
   - 每个线程都被赋予一个排序函数以及待排序列表的地址，并在分配完线程和内存栈后启动线程执行排序任务。
5. **线程执行完毕和资源释放**：
   - 在每个排序线程完成排序任务后，通过调用`task_exit`函数退出线程，并释放线程所使用的内存栈空间。

### **2、图形化排序过程**：（部分自带）

图形化排序过程在代码中通过使用图形库进行展示。在 `main` 函数中，首先初始化了图形模式，并获取了屏幕的分辨率。然后，根据需要排序的数据量和线程数量，将屏幕水平方向划分成了 N 个区域，每个区域用于展示一个排序算法的执行过程。

在每个排序线程中，通过调用 `line` 函数绘制不同颜色的线段来表示排序过程中的不同状态，例如清除之前的绘图痕迹、绘制当前的排序结果等。这些绘图操作使得用户可以直观地观察到排序算法的执行过程和排序结果。

举例来说，在 `sort_thread_1` 函数中，使用了选择排序算法来对列表进行排序。在每次交换元素之前，通过绘制黑色线段清除之前的绘图痕迹，然后绘制红色线段表示当前操作，最后经过一段时间的延迟后，绘制蓝色线段表示交换后的结果。这样的操作使得用户可以看到排序算法每一步的执行过程，加深对算法的理解。

### 3、**内存管理和优化**：（\_\_main 也是自带的）

1. **内存池的使用**：
   - 在 `__main` 函数中，使用了 TLSF 内存池来管理堆内存。通过调用 `tlsf_create_with_pool` 函数创建了一个 TLSF 内存池，并将其用于动态内存分配。
   - 这种内存池的使用可以减少堆内存的碎片化，提高内存分配和释放的效率，同时还能够减少内存泄漏的风险。
2. **动态内存分配和释放**：
   - 在 `create_sort_threads` 函数中，动态地分配了线程栈的内存空间，并在每个排序线程完成任务后释放了该内存空间，避免了内存泄漏问题。
   - 通过调用 `malloc` 和 `free` 函数进行内存的分配和释放，确保了内存的有效利用和及时释放。
3. **栈空间的优化**：
   - 在 `create_sort_threads` 函数中，为每个线程分配了一块独立的内存栈空间。通过控制栈空间的大小，可以避免栈溢出的问题，并优化了线程的执行效率。
   - 通过动态分配栈空间，使得每个线程都能够在需要的情况下获得足够的栈空间，避免了栈空间不足导致的程序崩溃或异常退出。
4. **系统调用的优化**：
   - 在 `sort_thread_1`、`sort_thread_2`、`sort_thread_3`、`sort_thread_4` 和 `sort_thread_5` 函数中，使用了 `nanosleep` 函数来进行线程的睡眠，以模拟排序过程中的延迟效果。
   - 这种睡眠操作的使用可以减少线程的 CPU 占用率，降低系统负载，提高系统的响应速度和稳定性。

通过以上的内存管理和优化措施，代码在运行时能够更高效地利用系统资源，提高了程序的性能和稳定性。

### **4、系统调用和图形界面的集成**：

1. **图形模式的初始化和退出**：
   - 在 `main` 函数中，首先调用了 `init_graphic` 函数初始化了图形模式，设置了屏幕分辨率和颜色模式等参数，为后续的图形绘制做准备。
   - 在排序任务完成后，调用了 `exit_graphic` 函数退出图形模式，释放了图形资源，结束图形界面的显示。
2. **图形绘制**：
   - 在排序线程的执行过程中，通过调用 `line` 函数来进行图形绘制，清除之前的绘图痕迹并绘制当前的排序结果。
   - 在排序过程中，不同颜色的线段代表不同的排序状态或操作，通过这种方式直观地展示了排序的过程和结果。
3. **系统调用的模拟**：
   - 在每个排序线程的执行过程中，通过调用 `nanosleep` 函数来进行线程的睡眠，模拟排序过程中的延迟效果。
   - 这种延迟操作能够使得排序过程以一定的速度展示在图形界面上，提高了可视化效果。
4. **多线程的集成**：
   - 代码通过创建多个排序线程来实现多线程排序，每个排序线程负责执行特定的排序算法。
   - 通过多线程的并发执行，提高了排序算法的效率，加快了排序过程。

综上所述，系统调用和图形界面在代码中紧密集成，通过图形界面直观地展示了排序算法的执行过程和结果，提高了用户体验和程序的可视化效果。

### **5、线程间同步和协作**：

1. **线程睡眠和延迟**：
   - 在每个排序线程的执行过程中，通过调用 `nanosleep` 函数来进行线程的睡眠，模拟排序过程中的延迟效果。
   - 这种延迟操作能够使得排序过程以一定的速度展示在图形界面上，提高了可视化效果。
2. **图形绘制和刷新**：
   - 在每次排序操作后，通过绘制不同颜色的线段来清除之前的绘图痕迹并绘制当前的排序结果，以在图形界面上展示排序过程。
   - 通过不断更新图形界面的显示，实现了排序过程的动态展示和实时刷新。
3. **线程退出和资源释放**：
   - 在每个排序线程完成排序任务后，通过调用 `task_exit` 函数退出线程，释放了线程所使用的内存栈空间。
   - 这样可以确保线程在完成任务后能够及时退出，释放资源，避免资源泄露和内存占用过多的问题。

综上所述，线程间同步和协作代码中通过线程的睡眠、图形绘制的刷新以及线程的退出和资源释放等方式得到了体现，保证了多个排序线程之间的协调和同步，使得排序过程能够顺利进行并展示在图形界面上。
