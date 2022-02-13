## Assignment 2

Upload the solution of Exercise 1(a, b), Exercise 2(a, b), and Exercise 3(a, b). Note that functions of Exercise-2 use the functions implemented in Exercise-1, and those implemented in Exercise-3 use the functions implemented in Exercise-2.

### Instructions to compile

Simply run the following line in the terminal
```
❯ ./run.sh
```

### Sample Output
```
--------------------------------------------------------
Input file: input/input10.txt
Total addition time is 0.018000 ms.
Average deletion time is 0.000167 ms.
--------------------------------------------------------
Input file: input/input100.txt
Total addition time is 0.059000 ms.
Average deletion time is 0.000167 ms.
--------------------------------------------------------
Input file: input/input10000.txt
Total addition time is 2.607000 ms.
Average deletion time is 0.000167 ms.
```

> Note: The outputs above correspond to the time measured using `sys/time.h` utilities. The `gprof` outputs for the 3 input files have been saved in the `prof_output10`, `pro_output100` and `prof_output10000` files which will be generated automatically when you execute `./run.sh`
