# Logical forks()

## Problem Statement
Generate multiple children for a given parent process using logical operators taking advantage of short circuit evaluation.
We assume fork() never fails.
> Note: I dont think there is any difference when compiled into assembly, but the constraint is quite interesting

## Guide
Consider **x1**
>int mask = ( a = fork() ) && (b = fork() );
#
Here the parent process has two children. a & b store their pids. In total only three calls can be made

| a | b |
|---|---|
| 0 |   |
| 1 | 0 |
| 1 | 1 |
