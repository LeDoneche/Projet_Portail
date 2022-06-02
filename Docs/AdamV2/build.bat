@echo off
set MGW=C:\Programs\CodeBlocks\MinGW\bin
set PATH=%PATH%;%MGW%

set CC=g++
set file=adam

rem -- main
if not exist %MGW%\%CC%.exe (
	echo %MGW%\%CC%.exe does not exist
	goto EOF
	)

rem -- build exe
echo compiling... %file%.cpp
%MGW%\%CC%.exe -DWIN32 -D_WIN32_WINNT=0x0601 -Wall -Weffc++ -pedantic -Wextra -std=c++17 -fPIC -I..\AdamV2\lib -g -c %file%.cpp -o %file%.o 2>NUL
%MGW%\%CC%.exe -o %file%.exe %file%.o -static-libstdc++ ..\AdamV2\lib\libsocket++.a -lws2_32

del /q *.o 1>NUL 2>NUL

echo run... %file%.exe
.\%file%.exe

:EOF
pause