@ECHO OFF
SET PATH=%~dp0bin;%~dp0MinGW\msys\1.0\bin;%~dp0MinGW\bin;%~dp0GnuWin32\bin;%PATH%

SET BXSHARE=%~dp0Bochs
SET QEMUHOME=%~dp0Qemu

SET PATH=%BXSHARE%;%QEMUHOME%;%PATH%

%ComSpec% /k "cd /d %~dp0epos && make debug"

::START /D Notepad++ notepad++.exe

 
