#include "rb_tree.h"

/* Valor de sentinela, indica que chegamos em alguma folha ou entao
 a raiz da arvore */
Node NIL_NODE;

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
    ret_val->left = NULL;
    ret_val->right = NULL;
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
Node* tree_insert(Node** T, int key){
    Node* r = *T;

    if(!r) {
        /*r = malloc(sizeof(Node));
        r->key = key;
        r->left = NULL;
        //r->right = NULL;*/
        r = (new_node(key));
        T = &r;
        return *T;
        //return *T;
    }
/*
    if(key > r->key) {
        r->right = tree_insert(&(r->right), key);
    }

    if(key < r->key) {
        r->left = tree_insert(&(r->left), key);
    }

    return r;
    */
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