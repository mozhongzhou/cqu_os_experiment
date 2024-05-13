/**
 * vim: filetype=c:fenc=utf-8:ts=4:et:sw=4:sts=4
 */
#include <stddef.h>
#include "kernel.h"
// 当前信号量指针
struct sem *sem_cur;
// 信号量空间头部
struct sem *sem_start;
int num = 0;

/**
 * sys_sem_create(int value): 创建一个新的信号量，并将其初始值设置为value。
 * 如果是第一个创建的信号量，那么就分配一块新的内存给sem_cur，并将sem_start设置为sem_cur。
 * 否则，将sem_cur设置为sem_start后面的一个位置。
 * 最后，将信号量的值设置为value，并将等待队列设置为NULL。
 */
int sys_sem_create(int value)
{
    if (!num)
    {
        sem_cur = (struct sem *)kmalloc(sizeof(struct sem));
        sem_start = sem_cur;
    }
    else
    {
        sem_cur = sem_start + num * sizeof(struct sem);
    }
    sem_cur->value = value;
    sem_cur->wq_kbd = NULL;
    num++;
    return (num - 1);
}
/**
 * sys_sem_destroy(int semid): 销毁一个已经存在的信号量。
 * 如果semid在有效范围内（即0到num之间），那么就释放对应的内存，并将信号量的数量减一。
 */
int sys_sem_destroy(int semid)
{ // 0<=semid<num
    if (semid < num && semid >= 0)
    {
        sem_cur = sem_start + semid * sizeof(struct sem);
        kfree(sem_cur);
        num--;
        return 0;
    }
    else
    {
        return -1;
    }
}
/**
 * sys_sem_wait(int semid): 对一个已经存在的信号量进行等待操作。
 * 如果semid在有效范围内，那么就将对应的信号量的值减一。
 * 如果信号量的值小于0，那么就将当前进程放入等待队列。
 */
int sys_sem_wait(int semid)
{ // 0<=semid<num
    if (semid < num && semid >= 0)
    {
        uint32_t f;
        // 为实现互斥
        save_flags_cli(f);
        sem_cur = sem_start + semid * sizeof(struct sem);
        sem_cur->value--;
        if (sem_cur->value < 0)
        {
            sleep_on(&sem_cur->wq_kbd);
        }
        restore_flags(f);
        return 0;
    }

    else
    {
        return -1;
    }
}
/**
 * sys_sem_signal(int semid): 对一个已经存在的信号量进行信号操作。
 * 如果semid在有效范围内，那么就将对应的信号量的值加一。
 * 如果信号量的值小于或等于0，那么就唤醒等待队列中的一个进程。
 */
int sys_sem_signal(int semid)
{ // 0<=semid<num
    if (semid < num && semid >= 0)
    {
        uint32_t f;
        save_flags_cli(f);
        sem_cur = sem_start + semid * sizeof(struct sem);
        sem_cur->value++;
        if (sem_cur->value <= 0)
        {
            wake_up(&(sem_cur->wq_kbd), 1);
        }
        restore_flags(f);
        return 0;
    }
    else
    {
        return -1;
    }
}
