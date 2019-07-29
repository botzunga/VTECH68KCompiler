del basic.bin
vasmm68k_mot_win32.exe basic68k.asm -Fbin -o basic.bin
..\RemoteReset.exe
GenProgramBIN.exe
del ..\DISK\PROGRAM.BIN
COPY PROGRAM.BIN ..\DISK\PROGRAM.BIN
pause