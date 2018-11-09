#ifndef RB_TREE_H_INCLUDED
#define RB_TREE_H_INCLUDED

#define PAR(x)  (x)->parent
#define GPAR(x) (x)->parent->parent

#include <stdio.h>
#include <stdlib.h>



typedef enum {RED, BLACK} Color;

typedef struct Node{
    int          key;
    Color        color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

void left_rotate(Node** T, Node* x);
void right_rotate(Node** T, Node* x);
Node* rb_insert_fixup(Node** T, Node** z);
Node* randomTree(int nNodes);

#endif // RB_TREE_H_INCLUDED
