#include <time.h>
#include "rb_tree.c"

extern Node* NIL_PTR;

void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

Node* randomTree(int nNodes) {
    Node* T = NULL;
    int* array = malloc(sizeof(int)*nNodes);

    int i;
    for(i = 0 ; i < nNodes ; i++) {
        array[i] = i;
    }
    shuffle(array, nNodes);
    for(i = 0 ; i < nNodes ; i++) {
        printf("%d\n", array[i]);
        T = rb_insert(&T, array[i]);
    }

    return T;
}

int main() {
    Node* n = NULL;
    n = rb_insert(&n, 100);
    n = rb_insert(&n, 90);
    n = rb_insert(&n, 110);
    n = rb_insert(&n, 80);
    n = rb_insert(&n, 79);

    printf("ERD\n");
    erd(n);
    printf("\n");
    //As vezes dá segmentation fault quando há rotações duplas
    return 0;
}

