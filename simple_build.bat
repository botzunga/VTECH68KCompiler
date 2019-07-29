@ECHO OFF
cd "C:\Users\Andrea\Desktop\68KCompiler"
buildeurV2.exe --infile in\PROGRAM.ASM --outfile out\PROGRAM.BIN --8to16 --pcrd-send
DEL PROGRAM.BIN
DEL PROGRAM.HEX