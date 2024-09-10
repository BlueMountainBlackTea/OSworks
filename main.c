#include<stdio.h>
#include "treeHeap.h"


void printData(void* x)
{
    printf("%d ", *(int*) x);
}


int main()
{
    //TODO::INIT constructor and destructor
    HeapContainer hp = {0};
    
    node root = {.data = 0, .id = 0, .left = NULL, .right = NULL, .level = 0, .levelID = 0, .parent = NULL, .next = NULL};
    root.head = &root;

    hp.root = &root;
    hp.last = &root;
    hp.printData = printData;
    

    push(&hp, 1);
    push(&hp, 2);
    push(&hp, 3);
    push(&hp, 4);
    push(&hp, 5);

    printHeap(&hp);

    buildHeap(&hp);
    printHeap(&hp);

    return 0;
}