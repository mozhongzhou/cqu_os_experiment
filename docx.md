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
