#include <time.h>
#include "rb_tree.c"

extern Node* NIL_PTR;

Node* randomTree(int nNodes) {
    Node* T = NULL;
    srand(time(NULL));

    int i, random = 0;
    for(i = 0 ; i < nNodes ; i++) {
        random = rand() % nNodes + 1;
        printf("%d - %d\n", i, random);
        T = rb_insert(&T, random);
        //printf("%d", random);
    }
    return T;
}

int main() {
    Node* n = NULL;
    n = rb_insert(&n, 20);
    n = rb_insert(&n, 12);
    n = rb_insert(&n, 10);
    //n = rb_insert(&n, 24);
    //n = rb_insert(&n, 13);
    //n = rb_insert(&n, 14);

    //n = randomTree(10);
    erd(n);
    printf("\n");

    return 0;
}

