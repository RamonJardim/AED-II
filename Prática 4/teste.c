#include "rb_tree.c"

// rotação e flip para essa semana

extern Node* NIL_PTR;

int main() {
    Node* n;
    n = tree_insert(&n, 44);
    printf("%d\n",n->key);
    erd(n);

    return 0;
}