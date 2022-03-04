#!/bin/bash

make clean
make

# mkdir output

./main input/100 output/100 100
./main input/5000 output/5000 5000
./main input/10000 output/10000 10000
./main input/100000 output/100000 100000
./main input/1000000 output/1000000 1000000
./main input/10000000 output/10000000 1000000