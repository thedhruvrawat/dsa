## Compilation

```
❯ gcc -c compare_at.c
❯ gcc -c compare_et.c
❯ gcc -c seqListOps.c
❯ gcc -o exe_at main.c seqListOps.o compare_at.o
❯ gcc -o exe_et main.c seqListOps.o compare_et.o
```

## Output

>Create an executable called `exe_at`, that will perform the above said operations based on Highest priority and lowest arrival time.

```
❯ ./exe_at

JOB ID = 3, Priority = 2, Execution time = 12, Arrival time = 11 
JOB ID = 6, Priority = 2, Execution time = 11, Arrival time = 12 
JOB ID = 9, Priority = 2, Execution time = 10, Arrival time = 13 
JOB ID = 8, Priority = 1, Execution time = 4, Arrival time = 7 
JOB ID = 5, Priority = 1, Execution time = 2, Arrival time = 8 
JOB ID = 2, Priority = 1, Execution time = 3, Arrival time = 9 
JOB ID = 1, Priority = 0, Execution time = 5, Arrival time = 1 
JOB ID = 10, Priority = 0, Execution time = 15, Arrival time = 2 
JOB ID = 7, Priority = 0, Execution time = 9, Arrival time = 3 
JOB ID = 4, Priority = 0, Execution time = 7, Arrival time = 4 
```

>Create an executable called `exe_et`, that will perform the above said operations based on Highest priority and lowest execution time.

```
❯ ./exe_et

JOB ID = 9, Priority = 2, Execution time = 10, Arrival time = 13 
JOB ID = 6, Priority = 2, Execution time = 11, Arrival time = 12 
JOB ID = 3, Priority = 2, Execution time = 12, Arrival time = 11 
JOB ID = 5, Priority = 1, Execution time = 2, Arrival time = 8 
JOB ID = 2, Priority = 1, Execution time = 3, Arrival time = 9 
JOB ID = 8, Priority = 1, Execution time = 4, Arrival time = 7 
JOB ID = 1, Priority = 0, Execution time = 5, Arrival time = 1 
JOB ID = 4, Priority = 0, Execution time = 7, Arrival time = 4 
JOB ID = 7, Priority = 0, Execution time = 9, Arrival time = 3 
JOB ID = 10, Priority = 0, Execution time = 15, Arrival time = 2  
```