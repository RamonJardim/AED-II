#ifndef RB_TREE_H_INCLUDED
#define RB_TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


typedef enum {RED, BLACK} Color;

typedef struct Node{
    int          key;
    Color         color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

#endif // RB_TREE_H_INCLUDED
