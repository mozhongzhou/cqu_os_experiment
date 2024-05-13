# 操作系统第四次实验报告

20220815 2024/4/28

## 一、任务记录

（1）在 kernel/sem.c 中用实现信号量的数据结构和四个基本操作的系统调用
（2）基本操作使用实验 ppt 里提到的 save_flags_cli(flags), restore_flags(flags)，wake_up()和 sleep_on()去实现
（3）用信号量实现生产者消费者模型，参考课程 ppt 关于 producer-consumer 的信号量实现代码的结构

## 二、代码理解

某一个版本 出现了一些 bug
/\*

- vim: filetype=c:fenc=utf-8:ts=4:et:sw=4:sts=4
  \*/
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
extern void \*g_heap;

// 这个是优先级的范围
#define PRI_USER_MIN 0
#define PRI_USER_MAX 127

// 间隔值：用于描绘 nice 实体
#define emp2 2

// 这个为数组大小
#define N 200

/\*_
在生产者-消费者模型中，使用信号量的典型实现如下：
使用一个信号量 empty 来表示缓冲区中空闲的位置数量。
使用一个信号量 full 来表示缓冲区中已填入数据的位置数量。
生产者在向缓冲区中插入数据之前，必须获取 empty 信号量，以确保缓冲区中有空闲位置可用。
消费者在从缓冲区中取出数据之前，必须获取 full 信号量，以确保缓冲区中有数据可用。
生产者向缓冲区中插入数据后，会释放 full 信号量，表示有数据可用。
消费者从缓冲区中取出数据后，会释放 empty 信号量，表示有空闲位置可用。
_/
void sort_bubble(int ary[], int curConsumer);
void tsk_control(void *pv);
void tsk_producer(void *pv);
void tsk_consumer(void \*pv);

static int mutex; // 互斥信号量 （初始值为 1 表示一次只能有 1 个线程访问缓冲区
static int full; // 消费者在从缓冲区中取出数据之前，必须获取 full 信号量，以确保缓冲区中有数据可用
static int empty; // 生产者在向缓冲区中插入数据之前，必须获取 empty 信号量，以确保缓冲区中有空闲位置可用

int curProducer = 0; // 当前生产者到第几个操作块 注意乘以 width
int curConsumer = 0; // 当前消费者到第几个操作块 注意乘以 width

int Ary[N];
int tempAry[N];

// 定义为全局变量方便多个函数调用
int tid_producer, tid_consumer, tid_control;

/\*\*

- GCC insists on \_\_main
- http://gcc.gnu.org/onlinedocs/gccint/Collect2.html
  _/
  void \_\_main()
  {
  size_t heap_size = 32 _ 1024 * 1024;
  void *heap_base = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
  g_heap = tlsf_create_with_pool(heap_base, heap_size);
  }

/\*\*

- 第一个运行在用户模式的线程所执行的函数
  \*/

void main(void \*pv)
{
mutex = sem_create(1); // 互斥信号量 （初始值为 1 表示一次只能有 1 个线程访问缓冲区
full = sem_create(0); // 消费者在从缓冲区中取出数据之前，必须获取 full 信号量，以确保缓冲区中有数据可用
empty = sem_create(5); // 生产者在向缓冲区中插入数据之前，必须获取 empty 信号量，以确保缓冲区中有空闲位置可用
// 启用图形化界面
int mode = 0x143;
init_graphic(mode);

    // 随机生成测试数组
    srand(time(NULL));
    int i;
    int width = g_graphic_dev.XResolution / 10;
    for (i = 0; i < N; i++)
    {
        Ary[i] = rand() % width; // 控制横着的宽度 不会超过边界
        tempAry[i] = Ary[i];
    }

    // 开辟空间给线程
    unsigned int stack_size = 1024 * 1024;
    unsigned char *stack_producer = (unsigned char *)malloc(stack_size);
    unsigned char *stack_consumer = (unsigned char *)malloc(stack_size);
    unsigned char *stack_control = (unsigned char *)malloc(stack_size);

    // 分配空间给生产者
    tid_producer = task_create(stack_producer + stack_size, &tsk_producer, (void *)0);
    setpriority(tid_producer, 63);

    // 分配空间给消费者
    tid_consumer = task_create(stack_consumer + stack_size, &tsk_consumer, (void *)0);
    setpriority(tid_consumer, 63);

    // 分配空间给控制
    tid_control = task_create(stack_control + stack_size, &tsk_control, (void *)0);
    setpriority(tid_control, 0);

    // 等待线程结束 （事实上不会结束）
    task_wait(tid_producer, NULL);
    task_wait(tid_consumer, NULL);
    task_wait(tid_control, NULL);

    // 释放信号量
    sem_destroy(mutex);
    sem_destroy(full);
    sem_destroy(empty);

    // 释放空间
    free(tid_producer);
    free(tid_consumer);
    free(tid_control);

    while (1)
        ;

    task_exit(0);

}

void sort_bubble(int ary[], int curConsumer)
{
int i, j, temp = 0;
int gap = 2;

    for (i = 1; i < N; i++)
    {
        for (j = i; j > 0; j--)
        {
            if (ary[j] < ary[j - 1])
            {
                line(curConsumer, (j - 1) * gap, curConsumer + ary[j - 1], (j - 1) * gap, RGB(0, 0, 0));
                temp = ary[j];
                ary[j] = ary[j - 1];
                ary[j - 1] = temp;
                line(curConsumer, (j - 1) * gap, curConsumer + ary[j - 1], (j - 1) * gap, RGB(255, 165, 0));
                line(curConsumer, j * gap, curConsumer + ary[j], j * gap, RGB(255, 165, 0));
            }
        }
    }

}

void tsk*producer(void \_pv)
{
int i; // 循环变量
int width = g_graphic_dev.XResolution / 10;
int gap = 2;
while (1)
{
sem_wait(empty);
sem_wait(mutex);
for (i = 0; i < N; i++)
{
// 使用黑色线覆盖原有图像
line(curProducer * width, i _ gap, (curProducer + 1) _ width, i _ gap, RGB(0, 0, 0));
line(curProducer _ width, i _ gap, curProducer _ width + Ary[i], i \* gap, RGB(128, 0, 128));
}
curProducer = (curProducer + 1) % 10;

        struct timespec sleepTime;
        sleepTime.tv_sec = 0;          // seconds
        sleepTime.tv_nsec = 100000000; // nanoseconds
        nanosleep(&sleepTime, NULL);

        sem_signal(mutex);
        sem_signal(full);
    }
    task_exit(0);

}

void tsk_consumer(void \*pv)
{
int i;
// 分十份 每份占十分之一
int width = g_graphic_dev.XResolution / 10;
while (1)
{
sem_wait(full);
sem_wait(mutex);

        sort_bubble(tempAry, curConsumer * width); // 对消费者消费的数据进行排序
        for (i = 0; i < N; i++)
        {
            tempAry[i] = Ary[i];
        }
        curConsumer = (curConsumer + 1) % 10;

        struct timespec sleepTime;
        sleepTime.tv_sec = 0;          // seconds
        sleepTime.tv_nsec = 100000000; // nanoseconds
        nanosleep(&sleepTime, NULL);

        sem_signal(mutex);
        sem_signal(empty);
    }

}

void tsk*control(void \_pv)
{
/*
事实上这个 getpriority 和 setpriority 是获取、改变的 nice 值，nice 值越小优先级越高。
然而为了可视化，需要做一个运算，具体运算体现在 setpriority 函数中。
\*/
// 这里面的 line 是在可视化 nice
int i;
int nice_consumer = getpriority(tid_consumer); // 获取线程优先级
int nice_producer = getpriority(tid_producer);
// 左边

    for (i = 0; i <= nice_producer; i++) // 画出nice的实体
        line(g_graphic_dev.XResolution / 2 - i * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 - 25,
             g_graphic_dev.XResolution / 2 - i * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(128, 0, 128));
    // 右边
    for (i = 0; i <= nice_consumer; i++)
        line(g_graphic_dev.XResolution / 2 + i * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 - 25,
             g_graphic_dev.XResolution / 2 + i * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(255, 165, 0));
    do
    {
        int key = getchar();
        if (key == 0x4800) // up 提高生产者producer的优先度
        {
            nice_producer = nice_producer + 1;
            if (nice_producer > PRI_USER_MAX)
                nice_producer = PRI_USER_MAX;
            setpriority(tid_producer, PRI_USER_MAX - nice_producer);
            line(g_graphic_dev.XResolution / 2 - nice_producer * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 - 25,
                 g_graphic_dev.XResolution / 2 - nice_producer * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(128, 0, 128));
        }
        else if (key == 0x5000) // down 降低生产者prouducer的优先度
        {
            line(g_graphic_dev.XResolution / 2 - nice_producer * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 - 25,
                 g_graphic_dev.XResolution / 2 - nice_producer * emp2 - 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(0, 0, 0)); // 消失涂黑
            nice_producer = nice_producer - 1;
            if (nice_producer < PRI_USER_MIN)
                nice_producer = PRI_USER_MIN;
            setpriority(tid_producer, PRI_USER_MAX - nice_producer);
        }
        if (key == 0x4D00) // right 提高消费者consumer的优先度
        {
            nice_consumer = nice_consumer + 1;
            if (nice_consumer > PRI_USER_MAX)
                nice_consumer = PRI_USER_MAX;
            setpriority(tid_consumer, PRI_USER_MAX - nice_consumer);
            line(g_graphic_dev.XResolution / 2 + nice_consumer * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 - 25,
                 g_graphic_dev.XResolution / 2 + nice_consumer * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(255, 165, 0));
        }
        else if (key == 0x4B00) // left 降低消费者consumer的优先度
        {
            line(g_graphic_dev.XResolution / 2 + nice_consumer * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 - 25,
                 g_graphic_dev.XResolution / 2 + nice_consumer * emp2 + 1, g_graphic_dev.YResolution * 3 / 4 + 25, RGB(0, 0, 0));
            nice_consumer = nice_consumer - 1;
            if (nice_consumer < PRI_USER_MIN)
                nice_consumer = PRI_USER_MIN;
            setpriority(tid_consumer, PRI_USER_MAX - nice_consumer);
        }
    } while (1); // 重复获取键盘输入

    task_exit(0);

}

## 三、进步

## 四、参考文献
