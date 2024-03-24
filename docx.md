在使用 vscode 之前，我的调试方式是根据 makefile 的.PHONY: qemudbg
qemudbg: MODE=debug
qemudbg: hd.img
ifeq ($(OS),Windows_NT)
	-start $(GDB)
	-qemu-system-i386w -S -gdb tcp::1234,nowait,nodelay,server,ipv4 -m 32 -boot order=c -vga std -hda $^ -L $(QEMUHOME)/Bios
else
ifeq ($(shell uname -s),Linux)
-/usr/bin/x-terminal-emulator -e $(GDB)
endif
ifeq ($(shell uname -s),Darwin)
-osascript -e 'on run argv' \
 -e ' tell application "Terminal" to do script "cd $(shell pwd); $(GDB)"' \
 -e 'end run'
endif
-qemu-system-i386 -S -gdb tcp::1234,nowait,nodelay,server,ipv4 -m 32 -boot order=c -vga std -hda $^
endif
通过 make clean debug 打开 qemu 和 gdb，然后在 gdb 中输入 target remote localhost：1234 进行连接，然后再通过

add-symbol-file kernel/eposkrnl.out 0x100000
add-symbol-file kernel/eposkrnl.out 0xc0100000 进一步调试，但是这样调试无法做到可视化，我该如何在 vscode 中调用内置 gdb 并且做到可视化代码调试？

{
"version": "0.2.0",
"configurations": [
{
"type": "gdb",
"request": "attach",
"name": "Attach to QEMU",
"target": "localhost:1234",
"remote": true,
"cwd": "${workspaceFolder}",
"gdbpath": "E:/mingw64/bin/gdb.exe"
}
]
}

我正在学习操作系统，我对 epos/kernel 和 epos/userapp 内的代码进行了修改。我最初的调试流程如下：打开 根目录下的 debug.bat：这会自动编译 epos/kernel 和 epos/userapp 内的文件，将编译内容存入 hd.img，然后通过 qemu 打开 hd.img.根据 makefile 的文件，打开的 qemu 会监听本地 1234 端口等待 gdb 连接，并会自动打开一个 gdb。我原先所需要做的就是在打开 bat 后，在自动打开的 gdb 中输入 target remote localhost:1234,然后通过 add-symbol-file kernel/eposkrnl.out 0x100000
add-symbol-file kernel/eposkrnl.out 0xc0100000 添加符号表，然后才能使用 break entry，continue 之类的调试指令进行调试。我的问题是如何利用 vscode 中方便快捷的打断点的方式来 debug 呢，能否避免输入 break 之类的 gdb 调试指令？

创建
int task_create(void *tos, void (*func)(void *pv), void *pv)
tos ：用户栈的栈顶指针
func ：线程函数
pv ：传递给线程函数 func 的参数
返回值 ：大于 0，则表示新创建线程之 ID
退出
int task_exit(int code_exit);
code_exit ：线程的退出代码
获取线程自己的 ID
int task_getid();
等待线程退出
int task_wait(int tid, int \*pcode_exit);
tid ：要等待线程之 ID
pcode_exit ：如果非 NULL，用于保存线程 tid 的退出代码

Step1：定义线程函数

void tsk_foo(void \*pv)
{  
 printf("This is task foo with tid=%d\r\n“, task_getid());
task_exit(0);//不能直接 return，必须调用 task_exit
}

Step2：申请线程栈

unsigned char *stack_foo;
unsigned int stack_size = 1024*1024;  
stack_foo = (unsigned char \*)malloc(stack_size );

线程退出后，才能把用户栈用 free 释放掉！
Step3：创建线程
int tid_foo;  
tid_foo = task_create(stack_foo+stack_size, &tsk_foo, (void \*)0);

随机生成 N 组非负整数列表，然后创建 N 个线程，分别用 N 种不同的排序算法对列表进行排序
N 必须大于 2
如何生成随机数？
Step1-播种：void srand(uint32_t seed)
seed 是随机数的种子，建议用实验（一）中实现的系统调用“time_t time(time_t \*loc)”
srand(time(NULL))

Step2-生成：多次调用“int rand()”获得随机数

进入图形模式，沿垂直方向把屏幕分成 N 个区域，每个排序线程用一个区域，动态显示排序过程。
如何进入图形模式？
调用 init_graphic(int mode)
mode=0x143
如何获取屏幕的分辨率？
水平：g_graphic_dev.XResolution，垂直：g_graphic_dev.YResolution
如何打点？
void setPixel(int x, int y, COLORREF cr);
(x, y)是点坐标
cr 是颜色，用宏定义 RGB(r,g,b)生成，其中 r,g,b 的取值范围都是 0-255
如何从 cr 中取出 r,g,b？用 getXValue(cr)，其中 X=R,G,B
如何画线？
void line(int x1, int y1, int x2, int y2, COLORREF cr);
如何退出图形模式？
int exit_graphic();

冒泡排序（Bubble Sort）：这是最简单的排序算法，它重复地遍历待排序的列表，每次比较两个相邻的元素，如果它们的顺序错误就把它们交换过来。这个算法的名字由来是因为越小的元素会经过交换慢慢“浮”到数列的顶端。

选择排序（Selection Sort）：这种排序算法是一种简单直观的排序算法，它的工作原理如下。首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。

插入排序（Insertion Sort）：插入排序是一种简单直观的排序算法，它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。

快速排序（Quick Sort）：快速排序使用分治法（Divide and conquer）策略来把一个序列（list）分为两个子序列（sub-lists）。步骤为：从数列中挑出一个元素，称为 "基准"（pivot），重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作。

归并排序（Merge Sort）：归并排序是建立在归并操作上的一种有效的排序算法,该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。它的基本操作是：将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为二路归并。

堆排序（Heap Sort）：堆排序是一种树形选择排序，是对直接选择排序的有效改进。堆的定义如下：具有 n 个元素的序列（h1,h2,…,hn),当且仅当满足（hi<=h2i,hi<=h2i+1）或（hi>=h2i,hi>=h2i+1）(i=1,2,…,n/2)时称之为堆。在这里只讨论满足前者条件的堆。由此，堆被看成一棵完全二叉树。

希尔排序（Shell Sort）：希尔排序，也称递减增量排序算法，是插入排序的一种更高效的改进版本。希尔排序是非稳定排序算法。希尔排序是基于插入排序的以下两点性质而提出改进方法的：插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率；但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位。

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

extern void _tlsf_create_with_pool(void_ mem, size_t bytes);
extern void \*g_heap;

void tsk_foo(void\* pv);
void sort_bubble(int ary[]);

/\*\*

- GCC insists on \_\_main
- http://gcc.gnu.org/onlinedocs/gccint/Collect2.html
  */
  void \_\_main()
  {
  size_t heap_size = 32*1024*1024;
  void *heap_base = mmap(NULL, heap_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
  g_heap = tlsf_create_with_pool(heap_base, heap_size);
  }

/\*\*

- 第一个运行在用户模式的线程所执行的函数
  */
  void main(void *pv)
  {
  printf("task #%d: I'm the first user task(pv=0x%08x)!\r\n",
  task_getid(), pv);

      //TODO: Your code goes here
      int mode = 0x143;
      init_graphic(mode);
      line(200, 0, 200, 600, RGB(255, 0, 0));

      unsigned char *stack_foo;
      unsigned int stack_size = 1024*1024;
      stack_foo = (unsigned char*)malloc(stack_size);

      int tid_foo;
      tid_foo = task_create(stack_foo + stack_size, &tsk_foo, (void *)0);
      task_wait(tid_foo, NULL);
      free(stack_foo);
      while(1)
          ;
      task_exit(0);

  }

void tsk_foo(void* pv){
printf("task tid = %d\r\n", task_getid());
int gap = 600/300;
srand(time(NULL));
int ary[300], temp = 0, i;
for(i=0; i<300; i++){
temp = rand() % 200;
ary[i] = temp;
line(0, i*gap, ary[i], i\*gap, RGB(255,0,0));
}
sort_bubble(ary);
task_exit(0);
}

void sort_bubble(int ary[]){
int i,j, temp = 0;
int gap = 600/300;

    for (i=1; i<300; i++){
        for (j=i; j>0; j--){
            if (ary[j]<ary[j-1]){
                line(0, (j-1)*gap, ary[j-1], (j-1)*gap, RGB(0,0,0));
                temp = ary[j];
                ary[j] = ary[j-1];
                ary[j-1] = temp;
                line(0, (j-1)*gap, ary[j-1],(j-1)*gap, RGB(255,0,0));
                line(0,j*gap, ary[j], j*gap, RGB(255,0,0));
            }
        }
    }

}
