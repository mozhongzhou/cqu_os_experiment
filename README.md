# 操作系统第三次实验报告

20220815 2024/4/7



## 一、任务记录

本次任务较为困难，参考了多个博客，以及跟多位同学讨论后方才实现代码

### 1、epos/kernel/kernel.h

新增

~~~cpp
//包含头文件 用于声明fixedpt类型变量
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







以下是对”fixedptc.h“的介绍

![image-20240416135503583](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240416135503583.png)

> 这段代码是在C++中定义了一些类型别名，这些别名是基于`FIXEDPT_BITS`宏的值。如果`FIXEDPT_BITS`等于32，那么就会定义以下类型别名：
>
> - `fixedpt`：这是一个32位有符号整数类型，对应的原始类型是`int32_t`。
> - `fixedptd`：这是一个64位有符号整数类型，对应的原始类型是`int64_t`。
> - `fixedptu`：这是一个32位无符号整数类型，对应的原始类型是`uint32_t`。
> - `fixedptud`：这是一个64位无符号整数类型，对应的原始类型是`uint64_t`。
>
> 这些类型别名通常用于简化代码和提高代码的可读性。在这个例子中，它们可能被用于处理固定点数，这是一种表示小数的方法，特别适用于不能使用浮点数的环境。



## 二、代码理解

















## 三、进步

target remote localhost:1234

add-symbol-file kernel/eposkrnl.out 0x100000

add-symbol-file kernel/eposkrnl.out 0xc0100000

break entry

continue

![image-20240413182309089](https://raw.githubusercontent.com/mozhongzhou/myPict_img/main/pic/image-20240413182309089.png)

遇到系统抛出异常 Un-handled exception 这是万万没想到的

编译方面的bug 解决了 结果无法进入图形化界面

为此我尝试了从来没用过的GDB来Debug

