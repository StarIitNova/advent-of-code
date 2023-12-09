@echo off

set OUTPUT=bin/aoc
set CFLAGS=-Isource/ -std=c++17 -D_AOC_USE_OSSL
set LFLAGS=

c++ %CFLAGS% -o %OUTPUT% source/%1.cpp source/tools/md5.cpp %LFLAGS% && bin\aoc.exe