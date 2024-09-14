# Logical forks()

## Problem Statement
Generate multiple children for a given parent process using logical operators taking advantage of short circuit evaluation.
We assume fork() never fails.
> Note: I dont think there is any difference when compiled into assembly, but the constraint is quite interesting

## Guide
Consider **x1**
```c
pid_t a = -1; pid_t b = -1;
int mask = ( a = fork() ) && (b = fork() );
```
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
#
What if we want moer then 2 children?
consider **x2**
```c
#ifdef x2
    pid_t a = -1; pid_t b = -1; pid_t c = -1;
    int mask = ( a = fork() ) && (b = fork()) && (c = fork());
    if (a == 0) prints(a);
    else if (b == 0) prints(b);
    else if (c == 0) prints(c);
    else prints(mask);
#endif
```
This creates three process a,b,c with 1 parent.
we can extend this for some n.
# Unraveled nested if-else
Notice how the if else statements are not nested unlike traditional forks()? This has to do with how the expression is evaluated as well as the values they can have. But it is kind of necessary to check them all on the order given if the following variables are not initialized. Here we have initialed them to -1 which is not exactly a good idea.
# mask
Ok, So what significane does the mask have? Well notice that mask is 1 only when all forks() return a non-zero value. if we only needed to access the parent process then checking ht e mask is enough.Consider **x3**
```c
pid_t a; pid_t b;
int mask = ( a = fork()) && (b= fork());
if (mask == 1) // a & b are non-zero
    ; // do something 
```

What happens if we use ```||``` instead of ```&&```? The children still belong to the same parent but the mask now has the value of 0 when all forks return 0. Consider **x4**
```c
#ifdef x4
    pid_t a, b,c;
    int mask = ( a = fork() ) || (b = fork()) || (c = fork());
    if (mask == 0)      //in process c
        prints(mask);
#endif
```
prints(mask) executes in process c since it must go thorugh the chain a = 0, b = 0, c = 0.
Thats all neat and all. But can we modify it to work on particular process? Say we have 5 different procs.
We are only concerned with executing some statements on process 3. Can we create a mask to do that?
We will get back to that, soon.

# Counting the number of processes
To count the number of processes we will be taking two approaches (which are the same but represented differently).
Method 1 involves building a short circuited table.
`fork() && fork() && fork()`
| a | b | c |
|---|---|---|
| 0 |   |   | 
| 1 | 0 |   | 
| 1 | 1 | 0 |
| 1 | 1 | 1 |

```python
    [    P    ]
         |
         |
    [    1    ] -------- [    0    ]            #first fork
         |
         |
    [    1    ] -------- [    0    ]            #second fork called by process P
         |
         |
    [    1    ] -------- [    0    ]            #third fork
    
```
In this structure P calls fork creating two children, one returning 0 and the other returning a non-zero (we assume it always return 1). In order to convert it into a parent-child binary tree from this sibling tree, we need to notice a few things. All the nodes growing up belong to the same node while the siblings becomes its children. 
So, we have
```python
    [    P    ]
|        |        |
|        |        |
[C1]    [C2]     [C3] 
```
#TODO


