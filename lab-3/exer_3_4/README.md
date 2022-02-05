## Assignment 1

Solve Exercise-4 with all other required functions. As an assignment, you need to only implement `cycle1.c`, i.e. *hare and the tortoise algorithm*. Create an excel file (`observations.xlsx`) with three columns: **value of N, Time Taken, Heap Space Used**. Put all the files (along with the excel file) in a folder, name the folder with your BITS ID, zip it, and upload it as a part of assignment.

### Instructions to compile

Simply run the following line in the terminal, to execute the *hare and tortoise algorithm* for detection of cycles in a linked list.
```
❯ make
```
And finally, to generate the output, run the executable file created.
```
❯ ./cycle.exe
```

You can check the observations for the *link-reversal algorithm* by modifying the 10th line of `makefile` with:

```makefile
$(CC) -g -Wall cycle2.o cycle.o alloc.o linkedlist.o -o $@ $(LFLAGS)
```

To run a fresh experiment simply run:
```
❯ make clean
```
### Sample Output
```
...
**********************************************************************
Cycle not detected
N: 1169282, elapsed time: 5.571000 ms. & heap space: 18708528
**********************************************************************
Cycle detected
N: 1752261, elapsed time: 14.108000 ms. & heap space: 28036192
**********************************************************************
Cycle not detected
N: 1813655, elapsed time: 9.925000 ms. & heap space: 29018496
**********************************************************************
...
```

> Note: All these observations will automatically be stored in `observations.xlsx` file created automatically. The number of observations has been set to 100.

For measuring the time using `gprof` use the following command -
```
❯ gprof cycle.exe gmon.out > prof_output
```
This will create a file `prof_output` containing the flat profile and function-wise time taken by the ptogram.

**Link to the observations file:** https://docs.google.com/spreadsheets/d/1c66HHV47ta52AMAU7nqV6TQzmAMwpkK7n8btwuRGAO0/edit?usp=sharing 