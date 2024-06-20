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
