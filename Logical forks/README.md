# Logical forks()

## Problem Statement
Generate multiple children for a given parent process using logical operators taking advantage of short circuit evaluation.
We assume fork() never fails.
> Note: I dont think there is any difference when compiled into assembly, but the constraint is quite interesting

## Guide
Consider **x1**
```c int mask = ( a = fork() ) && (b = fork() );```
#
Here the parent process has two children. a & b store their pids. In total only three calls can be made

| a | b |
|---|---|
| 0 |   |
| 1 | 0 |
| 1 | 1 |

```c
    //macro to print pids of process
    #define prints(a) printf("process:" #a " pid:%d, ppid:%d\n",getpid(),getppid())
    if (a == 0)
        prints(a);
    else if (b == 0)
        prints(b);
    else    //PARENT
        prints(mask);
```
For simplicity lets make that into a macro
