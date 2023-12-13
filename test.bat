@echo off

set OUTPUT=bin/aoc
set CFLAGS=-Isource/ -std=c++17 -O2
set LFLAGS=

echo -- Compiling AoC Script --
c++ %CFLAGS% -o %OUTPUT% source/%1.cpp source/tools/md5.cpp %LFLAGS%

IF %ERRORLEVEL% == 0 (
    echo -- Running AoC Output --
    bin\aoc.exe
) else (
    echo Compilation failed.
)