#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef HEAP_H
#define HEAP_H


typedef struct node {
    
    int data;
    int level;
    int levelID;
    int id;
    struct node* left;
    struct node* right;
    struct node* parent;
    struct node* next;
    struct node* head;
} node;

typedef void (*PrintDataFunction)(void*);
typedef struct 
{
    node* root;
    node* last;
    PrintDataFunction printData;
    int size;

} HeapContainer;


int max(int level)
{
    int value = 1;
    for (int i = 0 ; i< level; i++)
    {
        value *= 2;
    }
    return value - 1 ;
}

void push(HeapContainer* hp, int data)
{
    node* last = hp->last;
    node* tmp = (node*) malloc(sizeof(node));
    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->id = last->id + 1;
    tmp->next = NULL;

    if (last->levelID == max(last->level))
    {
        
        node *head = last->head;
        head->left = tmp;
        tmp->parent = head;
        tmp->head = tmp;
        tmp->level = last->level + 1;
        tmp->levelID = 0;
        
    }
    else
    {   
        tmp->head = last->head;
        tmp->level = last->level;
        tmp->levelID = last->levelID + 1;
        last->next = tmp;
        
        if ( (tmp->levelID) % 2 != 0) // same parent as last
        {
            tmp->parent = last->parent;
            tmp->parent->right = tmp;
        }
        else
        {
            tmp->parent = last->parent->next;
            tmp->parent->left = tmp;
        }
    }

    hp->last = tmp;
}

void printHeap(HeapContainer* hp) {
    assert(hp->printData != NULL);

    if (hp == NULL || hp->root == NULL) {
        printf("Heap is empty.\n");
        return;
    }

    node* ptr = hp->root;

    while(ptr != NULL)
    {
        hp->printData(&ptr->data);
        if (ptr->next == NULL)
        {
            ptr = ptr->head->left;
            printf("\n");
        }
        else
            ptr = ptr->next;
    }
    
}




//TODO
// Function to heapify a subtree rooted at a given node
void heapify(node* root) {
    if (root == NULL) return;

    node* largest = root;
    node* left = root->left;
    node* right = root->right;

    if (left && left->data > largest->data) largest = left;
    if (right && right->data > largest->data) largest = right;
    
    if (largest != root) {
        int temp = root->data;
        root->data = largest->data;
        largest->data = temp;
        heapify(largest);
    }
    
}

void buildHeap(HeapContainer* hp)
{
    node* ptr = hp->last->head->parent;
    
    while(ptr)
    {
        
        heapify(ptr);
        
        if (ptr->next == NULL)
        {
            ptr = ptr->head;
            
            if (ptr->parent != NULL)
            { 
                ptr = ptr->parent;
            }
            else 
                break;
        }
        else ptr = ptr->next;    
    }
}


#endif // HEAP_H