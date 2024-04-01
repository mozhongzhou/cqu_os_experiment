# 操作系统第一次实验报告

20220815 2024/3/17

---

## 任务记录

> •编写系统调用“time_t time(time_t \*loc)”
>
> –功能描述
>
> •返回从格林尼治时间 1970 年 1 月 1 日午夜起所经过的秒数。如果指针 loc 非 NULL，则返回值也被填到 loc 所指向的内存位置
>
> –数据类型 time_t 其实就是 long
>
> •typedef long time_t;

### 1、在 epos/kernel/machdep.c 添加函数（内核部分）

```cpp
time_t sys_time()
{
    time_t curTime = g_startup_time + g_timer_ticks / HZ;
    return curTime;
}
/*变量g_startup_time，它记录了EPOS启动时，距离格林尼治时间1970年1月1日午夜的秒数
变量g_timer_ticks
g_timer_ticks记录了EPOS启动以来定时器中断的总次数
宏定义HZ
HZ是定时器每秒钟中断的次数，即定时器中断的频率
*/
```

### 2、在 epos/kernel/kernel.h 添加函数声明（内核部分）

```cpp
time_t  sys_time();
```

### 3、在 epos/include/syscall-nr.h 中添加宏定义（内核部分）

```cpp
#define SYSCALL_time   2013
```

### 4、在 epos/kernel/machdep.c 的函数 syscall 中，增加“case SYSCALL_time”分支（内核部分）

> •读取参数的值
>
> time_t*loc = *(time_t \*\*)(ctx->esp+4);
>
> •调用系统调用的实现函数 sys_time
>
> ctx->eax=sys_time();
>
> if(loc != NULL)
>
> \*loc = ctx->eax;

```cpp
case SYSCALL_time:
    {
        time_t *loc = *(time_t **)(ctx->esp + 4);

        ctx->eax = sys_time();

        if (loc != NULL)
            *loc = ctx->eax;
    }
    break;
```

### 5、在 epos/userapp/lib/syscall-wrapper.S 末尾，加入汇编语言接口“WRAPPER(time)”（用户部分）

```cpp
WRAPPER(time)
```

### 6、在 epos/userapp/include/syscall.h 中，加入 C 语言声明 “time_t time(time_t \*loc);”（用户部分）

```cpp
time_t time(time_t *loc);
```

### 7、在 epos/userapp/main.c 中调用该系统调用，并打印出结果

```cpp
/**
 * 第一个运行在用户模式的线程所执行的函数
 */
void main(void *pv)
{
    printf("task #%d: I'm the first user task(pv=0x%08x)!\r\n",
           task_getid(), pv);

    // TODO: Your code goes here
    time_t t1, t2;
    t1 = time(&t2);
    if (t1 == t2)
        printf("t1 is equal to t2\n");
    else
        printf("t1 is not equal to t2\n");
    while (1)
        ;
    task_exit(0);
}

```

## 经验记录

总体而言经验多而杂

### 两个模拟器

Bochs：
Bochs 是一个完整的 x86 PC 模拟器，它可以模拟整个计算机系统，包括处理器、内存、存储设备、输入输出设备等。
Bochs 的目标是提供一个完整、准确的硬件模拟环境，以便于进行系统级别的开发、调试和测试。
由于 Bochs 模拟器的精确性和全面性，它的性能通常较低，适合用于调试和测试，而不太适合用于实际的生产环境或日常使用。

QEMU：
QEMU 是一个快速的处理器模拟器，它可以在主机平台上模拟多种处理器架构，包括 x86、ARM、MIPS 等。
QEMU 的主要目标是提供高性能的硬件模拟，以便于在不同的架构上运行不同的操作系统和应用程序。
QEMU 可以以系统模式或用户模式运行，系统模式下可以模拟完整的计算机系统，而用户模式下可以模拟单个应用程序的执行环境。
这两个模拟器都具有在不同平台上运行不同操作系统的能力，但它们的重点和设计目标略有不同。Bochs 更适用于系统级别的开发和调试，而 QEMU 更适用于在不同的架构上进行应用程序的测试和运行。

### GDB 断点调试指令：

#### 连接到在 localhost 的 1234 端口运行的远程 GDB 服务器。

target remote localhost:1234

#### 添加符号文件，这样 GDB 就可以知道函数和变量的名字。这个命令将 kernel/eposkrnl.out 文件的符号加载到内存地址 0x100000、0xc0100000

add-symbol-file kernel/eposkrnl.out 0x100000

add-symbol-file kernel/eposkrnl.out 0xc0100000

#### 在入口处设置断点

break entry

#### 继续

continue

#### 反汇编

disassemble entry

#### 单条指令 进入函数 以机器指令为单位

stepi

#### 单条指令 跳过函数 以机器指令为单位

nexti

#### 显示源代码

list

#### 单条语句 进入函数 以函数代码行为单位

step

#### 单条语句 跳过函数 以函数代码行为单位

next

> 以机器指令为单位和以源代码为单位，这两种方式的主要区别在于你在调试时关注的粒度。
>
> 以机器指令为单位：这种方式更接近硬件层面，你可以看到每一条机器指令的执行情况。这对于理解程序的底层执行过程，如寄存器的变化、内存的读写等，非常有用。但是，这种方式需要你对底层的机器指令有一定的理解。
>
> 以源代码为单位：这种方式更接近高级语言层面，你可以看到每一行源代码的执行情况。这对于理解程序的逻辑流程，如函数的调用、循环的执行等，非常有用。这种方式更适合大多数的软件开发和调试工作。
>
> 在 GDB 中，stepi 和 nexti 命令是以机器指令为单位进行步进，而 step 和 next 命令是以源代码为单位进行步进。

#### 可以打印变量的值

print xx

#### 查看所有断点的信息

info breakpoints

## 代码理解

**要搞懂代码首先得看懂架构**

文件夹说明：

**bin**: 这个文件夹通常用于存放可执行文件。

**bochs**: 这个文件夹可能包含了 Bochs 模拟器的相关文件。Bochs 是一个高度便携的开源 IA-32（x86）PC 模拟器，它模拟包括 CPU、内存、硬盘、显示、以太网等在内的硬件。

**epos**: 这个文件夹可能包含了 EPOS 操作系统的相关文件。EPOS 是一个面向嵌入式应用的开源操作系统。

**GnuWin32**: 这个文件夹可能包含了 GnuWin32 工具的相关文件。GnuWin32 提供了许多 GNU 开源工具的 Win32（Windows）版本。

**MinGW**: 这个文件夹可能包含了 MinGW 的相关文件。MinGW（Minimalist GNU for Windows）提供了一套开源的自由的 Windows 本地的 GNU 工具链，包括 GCC。

**Notepad++**: 这个文件夹可能包含了 Notepad++的相关文件。Notepad++是一个开源的代码编辑器。

**Qemu**: 这个文件夹可能包含了 QEMU 模拟器的相关文件。QEMU 是一个开源的处理器模拟器，它可以模拟多种处理器架构，并提供一些硬件模拟。

---

**epos** 文件内：

include: 这个文件夹通常用于存放头文件。

kernel: 这个文件夹通常用于存放内核源代码。

lib: 这个文件夹通常用于存放库文件。 包含了可被其他程序复用的代码

userapp: 这个文件夹通常用于存放用户应用程序源代码。

hd.img: 这个文件可能是一个硬盘镜像文件。硬盘镜像文件是一个包含了硬盘分区信息和文件系统的文件，它可以被用于模拟硬盘。

hd.img.bz2.txt: 这个文件可能是一个压缩文件。压缩文件是一个包含了经过压缩的文件或者文件夹的文件，它可以被用于节省存储空间。

Makefile: 这个文件可能是一个 Makefile 文件。Makefile 是一个用于管理源代码编译和链接的文件，它通常包含了一些编译和链接的规则。

Makefile.inc: 这个文件可能是一个 Makefile 包含文件。Makefile 包含文件是一个用于包含其他 Makefile 文件的文件，它可以被用于共享一些编译和链接的规则。

**kernel**:
bitmap.c:
bitmap.h:
bitmap.o:
cpu.h
dosfs.c
dosfs.h
dosfs.o
elf.c
elf.o
entry.o
entry.S 内核的入口点
eposkrnl.bin 内核的编译和链接结果 二进制格式的内核
eposkrnl.map 符号表
eposkrnl.out 其他格式的内核
fixedptc.h
floppy.c
floppy.o
frame.c
frame.o
ide.c
ide.o
kbd.c
kbd.o
kernel.ld 内核的链接脚本
kernel.h
kernel.ld.in 内核的链接脚本模板
kmalloc.c
kmalloc.o
machdep.c
machdep.h
machdep.o
make.dep
Makefile
mktime.c
mktime.o
multiboot.h
page.c
page.o
pci.c
pci.o
pe.c
pe.o
printk.c
printk.o
sem.c  
sem.o
startup.c
startup.o
task.c
task.o
timer.c
timer.o
vm86.c
vm86.o

**Makefile 部分：**

make run = make qemu
qemu 依赖于 hd.img
hd.img 依赖于 eposkrnl.bin 和 userapp 的 a.out
总的来说，当你执行 make run 时，Makefile 会首先编译 kernel 和 userapp，然后创建 hd.img，最后运行 qemu。所以，make run 会先编译后执行。

## 创新部分

vscode+gdb+qemu 可视化调试

流程：
启动 debug.bat
等待 qemu 启动（自动 pause）后打开 vscode
ctrl+shift+d 进入调试，启动 attach to QEMU 即可

这里遇到了些挑战，最多将 gdb 附到 vscode 上，还不能实现可视化断点调试。

---
