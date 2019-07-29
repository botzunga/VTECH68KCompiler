ReadFile(1, "C:\Users\Andrea\Desktop\68KCompiler\EhBASIC\basic.bin")
CreateFile(2, "C:\Users\Andrea\Desktop\68KCompiler\EhBASIC\progTEMP.bin")

*buf=AllocateMemory(1000000)
FileSeek(1, $210000)
result=ReadData(1, *buf, 1000000)
WriteData(2, *buf, result)


CloseFile(1)
CloseFile(2)

ReadFile(1, "C:\Users\Andrea\Desktop\68KCompiler\EhBASIC\progTEMP.bin")
CreateFile(2, "C:\Users\Andrea\Desktop\68KCompiler\EhBASIC\program.bin")

*LO=AllocateMemory(1)
*HI=AllocateMemory(1)

While(Not Eof(1))
  ReadData(1, *LO, 1)
  ReadData(1, *HI, 1)
  
  WriteData(2, *HI, 1)
  WriteData(2, *LO, 1)
  
Wend

; IDE Options = PureBasic 5.62 (Windows - x86)
; CursorPosition = 24
; FirstLine = 5
; EnableXP
; Executable = GenProgramBIN.exe