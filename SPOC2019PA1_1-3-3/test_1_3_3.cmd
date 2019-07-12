:loop
GenerateTestdata.exe >in.txt
std.exe <in.txt >std.out
test.exe <in.txt >test.out
fc std.out test.out
if not errorlevel 1 goto loop
pause
