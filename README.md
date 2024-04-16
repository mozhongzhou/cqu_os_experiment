# 操作系统第三次实验报告

20220815 2024/4/7

右边线程优先度高

![image-20240416145009474](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240416145009474.png)



左边线程优先度高

![image-20240416145056537](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240416145056537.png)





## 一、任务记录

本次任务较为困难，参考了多个博客，以及跟多位同学讨论后方才实现代码

### 1.0、epos/kernel/Makefile

 debug和run的CFLAGS添加-std=99

![image-20240416144410046](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240416144410046.png)

### 1.1、epos/kernel/kernel.h

新增三个宏定义，后续其他文件会用到

NZERO用于将系统态nice转换为用户态（非负数）

PRI_USER_MIN nice下限

PRI_USER_MAX nice上限

~~~cpp
#define NZERO 20
#define PRI_USER_MIN 0
#define PRI_USER_MAX 127
~~~

新增头文件

~~~cpp
//用于声明fixedpt类型变量
#include "fixedptc.h" 
~~~

struct tcb新增三个数据成员

~~~cpp
 // 动态优先级调度  nice、priority、estcpu声明
    int nice;
    int priority;
    fixedpt estcpu;
~~~

新增函数（获取和设置优先级函数，事实上获取和设置的是nice值 ）

~~~cpp
int sys_getpriority(int tid);
int sys_setpriority(int tid, int nice);
~~~

### 1.2、epos/kernel/task.c

函数sys_task_create

~~~cpp
   new->nice = 0; // 初始化nice
   new->estcpu = 0;
   new->priority = 0;
~~~

重写schedule

~~~cpp
/**
 * CPU调度器函数，这里（以前是）只实现了轮转调度算法 (现在是优先级调度算法)
 *
 * 注意：该函数的执行不能被中断
 */
void schedule()
{
    struct tcb *select = g_task_head;
    struct tcb *high = g_task_running;
    // 设置任务优先级（priority）
    while (select != NULL)
    {
        select->priority = PRI_USER_MAX - fixedpt_toint(fixedpt_div(select->estcpu, fixedpt_fromint(4))) - select->nice * 2;
        select = select->next;
    }
    select = g_task_head;
    // 选择优先级最高的任务：
    while (select != NULL)
    {
        if ((select->tid != 0) && (select->state == TASK_STATE_READY))
        {
            if (high->priority < select->priority)
            {
                high = select;
            }
            if (high->tid == 0)
                high = select;
        }
        select = select->next;
    }
    // 检查是否需要切换任务：
    if (high == g_task_running)
    {
        if (high->state == TASK_STATE_READY)
            return;
        high = task0;
    }
    // 标记是否需要重新调度：
    // 在整个调度过程结束后，将 g_resched 标志设为 0，表示不需要重新调度。 g_resched = 0;
    switch_to(high);
}
~~~

### 1.3、epos/kernel/timer.c

新增全局变量

~~~cpp
//定义全局变量
fixedpt g_load_avg = 0;
~~~

重写isr_timer

~~~cpp
/**
 * 定时器的中断处理程序
 */

void isr_timer(uint32_t irq, struct context *ctx)
{
  // 首先，在 isr_timer 函数中，全局计时器 g_timer_ticks 被递增，表示经过了一个时钟周期。
  g_timer_ticks++;
  if (g_task_running != NULL)
  {
    // 如果是task0在运行，则强制调度
    if (g_task_running->tid == 0)
    {
      g_resched = 1;
    }
    else
    {
      // 否则，把当前线程的时间片减一
      --g_task_running->timeslice;

      // 如果当前线程用完了时间片，也要强制调度
      if (g_task_running->timeslice <= 0)
      {
        g_resched = 1;
        g_task_running->timeslice = TASK_TIMESLICE_DEFAULT;
      }

      g_task_running->estcpu = fixedpt_add(g_task_running->estcpu, FIXEDPT_ONE);

      if (g_timer_ticks % HZ == 0)
      {
        int nready = 0; // nready represents the thread be already.
        struct tcb *tsk = g_task_head;
        while (tsk != NULL)
        {
          if (tsk->state == TASK_STATE_READY)
            nready++;

          fixedpt ratio;
          ratio = fixedpt_mul(FIXEDPT_TWO, g_load_avg);
          ratio = fixedpt_div(ratio, fixedpt_add(ratio, FIXEDPT_ONE));
          tsk->estcpu = fixedpt_add(fixedpt_mul(ratio, tsk->estcpu),
                                    fixedpt_fromint(tsk->nice));
          tsk = tsk->next;
        }

        // 对于所有状态为就绪的任务，代码会遍历它们，并根据一定的公式更新它们的 estcpu 值。
        // 这个公式中，除了一个固定的增量之外，还有一个根据任务的 nice 值计算出的增量。
        // nice 值是一个表示任务优先级的参数，较小的 nice 值意味着更高的优先级，较大的 nice 值意味着更低的优先级。
        // 因此，根据任务的 nice 值不同，它们的 estcpu 值会有所调整，影响了它们在多线程环境中的调度顺序。

        fixedpt r59_60 = fixedpt_div(fixedpt_fromint(59), fixedpt_fromint(60));
        fixedpt r01_60 = fixedpt_div(FIXEDPT_ONE, fixedpt_fromint(60));
        g_load_avg = fixedpt_add(fixedpt_mul(r59_60, g_load_avg),
                                 fixedpt_mul(r01_60, fixedpt_fromint(nready)));
      }
    }
  }
}
~~~

### 1.4、epos/kernel/mechdep.c

新增函数实现

~~~cpp
int sys_getpriority(int tid)
{
    //
    uint32_t flags;
    struct tcb *tsk;
    //
    save_flags_cli(flags);
    tsk = g_task_head;
    while (tsk != NULL)
    {
        if (tsk->tid == tid)
            break;
        tsk = tsk->next;
    }
    //
    restore_flags(flags);
    if (tsk == NULL) // 失败
        return -1;
    else // 设置nice值
        return tsk->nice + NZERO;
}

int sys_setpriority(int tid, int nice)
{
    int edgePrio = 2 * NZERO - 1;      // 39
    if (nice >= 0 && nice <= edgePrio) // 合理情况
    {
        if (tid == 0)
        {
            g_task_running->nice = nice - NZERO;
            return 0;
        }
        //
        uint32_t flags;
        struct tcb *tsk;
        //
        save_flags_cli(flags);
        tsk = g_task_head;
        while (tsk != NULL)
        {
            if (tsk->tid == tid)
                break;
            tsk = tsk->next;
        }
        //
        restore_flags(flags);
        if (tsk == NULL)
            return -1;
        else
            tsk->nice = nice - NZERO;
        return 0;
    }
    else
        return -1;
}

~~~

void **syscall**(struct **context** *ctx) 增添case

~~~Cpp
 case SYSCALL_getpriority:
    {
        int tid = *(int *)(ctx->esp + 4);
        ctx->eax = sys_getpriority(tid);
    }
    break;
    case SYSCALL_setpriority:
    {
        int tid = *(int *)(ctx->esp + 4);
        int nice = *(int *)(ctx->esp + 8);
        ctx->eax = sys_setpriority(tid, nice);
    }
    break;
~~~

### 1.5、epos/include/syscall-nr.h

新增宏定义

~~~cpp
#define SYSCALL_getpriority 50
#define SYSCALL_setpriority 51
~~~

### 1.6、epos/userapp/lib/syscall-warpperS

新增WRAPPER

~~~Cpp
WRAPPER(getpriority)
WRAPPER(setpriority)
~~~

### 1.7、epos/userapp/main.c

~~~Cpp
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

~~~

## 二、代码理解

### 2.0、关于CFALGS+=-stdc99

> run: CFLAGS+=-std=c99 -O2 -ggdb`：这一行为`run`目标添加了一些编译标志。`-std=c99`指定了C语言的版本为C99，`-O2`启用了优化，`-ggdb`启用了GDB调试。



### 2.1、关于”fixedptc.h“

![image-20240416135503583](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240416135503583.png)

> 这段代码是在C++中定义了一些类型别名，这些别名是基于`FIXEDPT_BITS`宏的值。如果`FIXEDPT_BITS`等于32，那么就会定义以下类型别名：
>
> - `fixedpt`：这是一个32位有符号整数类型，对应的原始类型是`int32_t`。
> - `fixedptd`：这是一个64位有符号整数类型，对应的原始类型是`int64_t`。
> - `fixedptu`：这是一个32位无符号整数类型，对应的原始类型是`uint32_t`。
> - `fixedptud`：这是一个64位无符号整数类型，对应的原始类型是`uint64_t`。
>
> 这些类型别名通常用于简化代码和提高代码的可读性。在这个例子中，它们可能被用于处理固定点数，这是一种表示小数的方法，特别适用于不能使用浮点数的环境。

### 2.2、关于void schedule()

> 这是一个CPU调度器函数，它使用优先级调度算法来决定下一个要运行的任务。这个函数的主要步骤如下：
>
> 1. 首先，它遍历所有的任务（task），并为每个任务设置一个优先级。优先级是由任务的`estcpu`（估计的CPU使用量）除以4，然后减去任务的`nice`值的两倍得到的。`nice`值是一个可以由用户设置的值，用来影响任务的优先级。`nice`值越高，优先级越低。
> 2. 然后，它再次遍历所有的任务，选择优先级最高的任务。如果有多个任务具有相同的最高优先级，那么它会选择第一个找到的任务。
> 3. 接下来，它检查是否需要切换任务。如果当前正在运行的任务的优先级仍然是最高的，并且该任务的状态是`TASK_STATE_READY`（即任务已经准备好运行），那么就不需要切换任务，函数直接返回。否则，它会切换到优先级最高的任务。
> 4. 最后，它调用`switch_to`函数来切换到选定的任务。
>
> 注意，这个函数假设所有的任务都链接在一个全局的任务列表`g_task_head`中，当前正在运行的任务存储在全局变量`g_task_running`中。

### 2.3、关于isr_timer

> 这是一个定时器的中断处理程序。当定时器产生一个中断时，这个函数会被调用。这个函数的主要步骤如下：
>
> 1. 首先，它增加全局计时器`g_timer_ticks`的值，表示经过了一个时钟周期。
> 2. 然后，它检查当前正在运行的任务。如果是`task0`在运行，那么它会设置全局变量`g_resched`为1，表示需要进行任务调度。
> 3. 如果不是`task0`在运行，那么它会减少当前任务的时间片。如果当前任务的时间片用完了，那么它也会设置`g_resched`为1，并重置当前任务的时间片为默认值。
> 4. 接下来，它增加当前任务的`estcpu`值，表示当前任务的CPU使用量。
> 5. 如果`g_timer_ticks`是`HZ`的倍数（`HZ`通常表示每秒的时钟中断数），那么它会遍历所有的任务，并更新它们的`estcpu`值和系统的平均负载`g_load_avg`。`estcpu`值的更新考虑了任务的`nice`值，`nice`值越小，优先级越高，`estcpu`值增加得越少。系统的平均负载是根据就绪状态的任务数计算的。
>
> 这个函数的主要作用是更新任务的状态和系统的状态，以便于任务调度器进行任务调度。

### 2.4、关于 getpriority和setpriority

> `sys_getpriority(int tid)`函数是用于获取任务的优先级。它首先保存当前的中断状态，并关闭中断，然后遍历任务列表，寻找ID为`tid`的任务。如果找到了这个任务，那么它会恢复中断状态，并返回任务的`nice`值加上`NZERO`。如果没有找到这个任务，那么它会恢复中断状态，并返回-1表示失败。
>
> `sys_setpriority(int tid, int nice)`函数是用于设置任务的优先级。它首先检查`nice`值是否在合理的范围内（0到2*`NZERO`-1）。如果`nice`值合理，那么它会检查`tid`是否为0。如果`tid`为0，那么它会设置当前运行任务的`nice`值，并返回0表示成功。如果`tid`不为0，那么它会保存当前的中断状态，并关闭中断，然后遍历任务列表，寻找ID为`tid`的任务。如果找到了这个任务，那么它会设置任务的`nice`值，并恢复中断状态，然后返回0表示成功。如果没有找到这个任务，那么它会恢复中断状态，并返回-1表示失败。如果`nice`值不合理，那么它会直接返回-1表示失败。



### 2.5、关于main函数

> 这段代码是一个简单的多线程程序，主要用于演示冒泡排序算法和线程优先级的概念。程序中创建了三个线程，每个线程执行不同的任务。
>
> 1. `main`函数：这是程序的入口点。它首先初始化了一个图形界面，然后创建了三个线程（tsk_1, tsk_2, tsk_3）并设置了它们的优先级。然后，它等待这三个线程完成执行。
> 2. `tsk_1`和`tsk_2`函数：这两个函数都是在执行冒泡排序算法。它们首先在屏幕上画出未排序的数组，然后对数组进行排序，排序过程中会在屏幕上更新排序的进度。
> 3. `sort_bubble1`和`sort_bubble2`函数：这两个函数实现了冒泡排序算法。在排序过程中，它们会在屏幕上画出排序的进度。
> 4. `tsk_3`函数：这个函数用于改变其他两个线程的优先级。它会不断地获取用户的键盘输入，根据用户的输入来提高或降低其他两个线程的优先级。
> 5. `__main`函数：这个函数是GCC编译器的特性，它会在main函数之前被调用。在这个函数中，它创建了一个堆内存池，供程序的其他部分使用。
>
> 总的来说，这个程序是一个很好的多线程和冒泡排序的演示，它展示了如何在多线程环境中使用冒泡排序，并且如何动态地改变线程的优先级。

## 三、进步

**感觉最大的收获是会用GDB调试了**



对于这个epos 在qemu里面运行，相当于套娃，不能直接调试epos代码，要通过gdb连接到qemu才行



起因是遇到系统抛出异常 Un-handled exception 这是万万没想到的 exception code 0x0e 也就是16进制14

![image-20240413182309089](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240413182309089.png)



编译方面的bug 解决了 结果无法进入图形化界面

为此我尝试了从来没用过的GDB来Debug

____



target remote localhost:1234

add-symbol-file kernel/eposkrnl.out 0x100000

add-symbol-file kernel/eposkrnl.out 0xc0100000

break entry 打断点

用list看目标周围函数

step单步进入

next单函数进入

finish跳出

continue



____



找到了程序的入口就在machdep.c

cstart开始

![image-20240416150732481](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240416150732481.png)

然后是初始化

![image-20240416150757391](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240416150757391.png)



![image-20240416150814063](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240416150814063.png)



最后也找到了异常点 知道为什么会出这些问题

![image-20240416151107275](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240416151107275.png)







## 四、参考博客

[《操作系统原理》实验三：线程的调度 - 灰信网（软件开发博客聚合） (freesion.com)](https://www.freesion.com/article/7047299456/)
