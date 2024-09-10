#include<stdio.h>
#include <unistd.h>
#include<sys/wait.h>
// #define x1
// #define x2
// #define x3
// #define x4
#define x5
#define prints(name) printf("process:" #name " pid:%d, ppid:%d\n",getpid(),getppid())

int main()
{

    #ifdef x1
    pid_t a = -1; pid_t b = -1;
    int mask = ( a = fork() ) && (b = fork() );

    if (a == 0)
    {
        prints(a);
    }
    else if (b == 0)
    {
        prints(b);
    }
    else    //PARENT
    {
        prints(mask);
    }
    #endif

    #ifdef x2
    pid_t a = -1; pid_t b = -1; pid_t c = -1;

    int mask = ( a = fork() ) && (b = fork()) && (c = fork());
    if (a == 0) prints(a);
    else if (b == 0) prints(b);
    else if (c == 0) prints(c);
    else prints(mask);
    #endif

    #ifdef x3
    pid_t a; pid_t b;
    int mask = ( a = fork()) && (b= fork());
    if (mask == 1) // a & b are non-zero
        prints(mask); // do something 
    #endif

    #ifdef x4
    pid_t a, b,c;
    int mask = ( a = fork() ) || (b = fork()) || (c = fork());
    if (mask == 0)      //in process c
        prints(mask);
    #endif

    #ifdef x5
    pid_t a,b,c,d,e;
    prints(mask);
    int mask = !( a = fork())  && !( b = fork() )  && ( c = fork() ) &&  !( d = fork())  && !( e = fork() )  ;
    if (mask == 1)
        prints(mask);
    

    if (a == 0) prints(a);
    else if (b == 0) prints(b);
    else if (c == 0) prints(c);
    else if (d == 0) prints(d);
    else if (e == 0) prints(e);
    
    #endif

    return 0;
}