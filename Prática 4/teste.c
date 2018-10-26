#include "rb_tree.c"

// rotação e flip para essa semana

extern Node* NIL_PTR;

int main() {
    Node* n = NULL;
    //n = new_node(12);
    n = rb_insert(&n, 44);
    //printf("%p\n\n\n\n", PAR(n));
    n = rb_insert(&n, 30);
    //printf("%d\n",n->key);
    //erd(n);

    return 0;
}