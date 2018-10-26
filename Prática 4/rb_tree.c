#include "rb_tree.h"

/* Valor de sentinela, indica que chegamos em alguma folha ou entao
 a raiz da arvore */
Node NIL_NODE = {.key = 213980,
                 .color = BLACK};

/* Ponteiro para o valor de sentinela */
Node *NIL_PTR = &NIL_NODE;

/** Funcao auxiliar que cria um novo Node, alocando memoria,
* para um valor de chave passado como parametro.
* Note que os valores dos ponteiros left/right/parent sao
* mantidos como NULL
*
* Parametros:
* key: a chave para o novo Node
*
* Devolve:
* Um novo Node em caso de sucesso, NULL caso nao consiga alocar
* a memoria para o novo Node
*/
Node* new_node(int key) {
    Node *ret_val = (Node*) malloc(sizeof(Node));
    if(NULL == ret_val) return NULL;
    ret_val->key = key;
    ret_val->color = RED;
    ret_val->left = NIL_PTR;
    ret_val->right = NIL_PTR;
    ret_val->parent = NULL;
    return ret_val;
}

/**
* A funcao abaixo insere uma nova chave em uma arvore RB
* sem realizar o balanceamento.
*
* Parametros:
* T: aponta para a raiz da arvore onde devemos inserir a chave
* key: valor da nova chave
*
* Devolve:
* O novo Node inserido em caso de sucesso, NULL caso nao
* seja possivel inserir o novo valor
*/
Node* rb_insert(Node** T, int key){

    if(NULL == (*T)){
        (*T) = new_node(key);
        PAR(*T) = NIL_PTR;
        return (*T);
    }

    Node* y = NIL_PTR;
    Node* x = *T;
    Node* z = new_node(key);

    while((x) != (NIL_PTR)) {
        y = x;
        if(key < y->key){
            x = x->left;
        } else {
            x = x->right;
        }
    }
    PAR(z) = y;
    if(y == NIL_PTR){
        (*T) = z;
    } else if(key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = NIL_PTR;
    z->right = NIL_PTR;
    z->color = RED;
    rb_insert_fixup(T, (&z));
    return (*T);
}

Node* rb_insert_fixup(Node** T, Node** z){
    Node* y;
    while(PAR(*z)->color == RED){
        if(PAR(*z) == GPAR(*z)->left){
            y = GPAR(*z)->right;
            if(y->color == RED){
                PAR(*z)->color = BLACK;
                y->color = BLACK;
                GPAR(*z)->color = RED;
            } else {
                if((*z) == PAR(*z)->right) {
                    (*z) = PAR(*z);
                    left_rotate(T, (*z));
                }
                PAR(*z)->color = BLACK;
                GPAR(*z)->color = RED;
                right_rotate(T, (*z));
            }
        } else {
            y = GPAR(*z)->left;
            if(y->color == RED){

                printf("%p, %d\n\n",y);

                //PAR(*z)->color = BLACK;
                //y->color = BLACK;
                //GPAR(*z)->color = RED;
            } /*else {
                if((*z) == PAR(*z)->left) {
                    (*z) = PAR(*z);
                    right_rotate(T, (*z));
                }
                PAR(*z)->color = BLACK;
                GPAR(*z)->color = RED;
                left_rotate(T, (*z));
            }*/
        }
    }
    (*T)->color = BLACK;
}

/**
* Realiza uma rotacao simples para a esquerda
*
* Parametros:
* T: aponta para a raiz da arvore onde a rotacao sera realizada
* x: Node pertencente a arvore em torno do qual faremos a rotacao
*
*/
void left_rotate(Node** T, Node* x) {
    Node* y = x->right;
    Node* b = y->left;
    y->parent = x->parent;
    x->parent = y;
    x->right = b;
    b->parent = x;
    y->left = x;
}

/**
* Realiza uma rotacao simples para a direita
*
* Parametros:
* T: aponta para a raiz da arvore onde a rotacao sera realizada
* x: Node pertencente a arvore em torno do qual faremos a rotacao
*
*/
void right_rotate(Node** T, Node* y) {
    Node* x = y->left;
    Node* b = x->right;
    x->parent = y->parent;
    y->parent = x;
    y->left = b;
    b->parent = y;
    x->right = y;
}


/**
* Realiza a troca de cor em alguns nos, caso esses satisfacam
* algumas condicoes.
*
* Parametros:
* T: aponta para a raiz da arvore onde a rotacao sera realizada
* x: Node pertencente a arvore em torno do qual faremos a rotacao
*
*/
void flip_color(Node** T, Node* x){
    Node* tio;
    Node* pai = x->parent;
    Node* vo  = x->parent->parent;

    if(x->parent->right != x) {
        tio = x->parent->right;
    } else {
        tio = x->parent->left;
    }

    if(x->color == RED && pai->color == RED && tio->color == RED && vo->color == BLACK){
        pai->color = tio->color = BLACK;
        vo->color = RED;
    }
}

void erd (Node *r) {
    if (r != NULL) {
        erd(r->left);
        printf("%d ", r->key);
        erd(r->right);
    }
}