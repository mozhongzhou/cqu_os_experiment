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
