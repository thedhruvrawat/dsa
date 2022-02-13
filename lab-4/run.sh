#!/bin/bash

make clean
make

./test.exe input/input10.txt
gprof test.exe gmon.out > prof_output10

./test.exe input/input100.txt
gprof test.exe gmon.out > prof_output100

./test.exe input/input10000.txt
gprof test.exe gmon.out > prof_output10000