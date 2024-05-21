@ECHO OFF
::这是一个命令，用于关闭在执行批处理文件时显示命令行命令的回显。在批处理文件中使用 @ 符号表示不要显示命令的执行结果。ECHO OFF 命令会关闭后续命令的回显，从而使批处理文件在执行时不会在命令行中显示命令。
SET PATH=%~dp0bin;%~dp0MinGW\msys\1.0\bin;%~dp0MinGW\bin;%~dp0GnuWin32\bin;%PATH%

::这一行用于设置系统的 PATH 环境变量。%~dp0 表示当前批处理文件的目录路径，而 %PATH% 表示系统当前的 PATH 环境变量。这一行将当前目录下的 bin 目录以及其他指定目录添加到系统的 PATH 环境变量中，以便系统可以找到这些目录下的可执行文件。
SET BXSHARE=%~dp0Bochs
SET QEMUHOME=%~dp0Qemu
::这两行分别定义了 BXSHARE 和 QEMUHOME 两个环境变量，并将它们设置为 Bochs 和 QEMU 的安装目录。%~dp0 表示当前批处理文件的目录路径。

SET PATH=%BXSHARE%;%QEMUHOME%;%PATH%
::这一行将 BXSHARE 和 QEMUHOME 两个环境变量的值添加到系统的 PATH 环境变量中，以便系统可以找到 Bochs 和 QEMU 的可执行文件。

 %ComSpec% /k "cd /d %~dp0epos && make run"


::START /D Notepad++ notepad++.exe

 
