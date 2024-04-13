# 操作系统第三次实验报告

20220815 2024/4/7

epos 代码压缩包

## 一、任务记录

### 1、epos/kernel/kernel.h 的 struct tcb 中增加线程的静态优先级 nice

![image-20240408145554222](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240408145554222.png)

增加后

![image-20240408145855780](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240408145855780.png)

### 2、epos/kernel/task.c/sys_task_create 初始化 nice 为 0

![image-20240408150335634](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240408150335634.png)

### 3、增加系统调用

task.c

![image-20240408154115813](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240408154115813.png)

kernel.h

![image-20240408154139712](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240408154139712.png)

SYSCALL

![image-20240408154726014](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240408154726014.png)

### 4、struct tcb 中，再增加两个属性

![image-20240408155317314](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240408155317314.png)

```cpp
 int estcpu;  // 线程最近使用了多少CPU时间

 int priority; //线程的动态优先级
```

## 二、代码理解

## 三、创新

target remote localhost:1234
add-symbol-file kernel/eposkrnl.out 0x100000
add-symbol-file kernel/eposkrnl.out 0xc0100000
break entry
continue
disassemble + point





![image-20240413182309089](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240413182309089.png)
