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
Node* rb_insert(Node** T, int key){
    if(NULL == (*T)){
        (*T) = new_node(key);
        PAR(*T) = NIL_PTR;
        (*T)->color = BLACK;
        (*T)->left = NIL_PTR;
        (*T)->right = NIL_PTR;
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
    Node* tmp;
    int rodou = 0;

    while(PAR(*z)->color == RED){
        if(PAR(*z) == GPAR(*z)->left){
            y = GPAR(*z)->right;
            if(y->color == RED){
                PAR(*z)->color = BLACK;
                y->color = BLACK;
                GPAR(*z)->color = RED;
            } else {
                if((*z) == PAR(*z)->right) {
                    GPAR(*z)->color = RED;
                    tmp = PAR(*z);
                    PAR(*z) = PAR(*z)->parent;
                    (*z)->left->parent = tmp;
                    tmp->right = (*z)->left;
                    (*z)->left = tmp;
                    tmp->parent = (*z);
                    PAR(*z)->left = (*z);
                    tmp->parent = (*z);
                    rodou = 1;

                }
                
                if(GPAR(*z) != NIL_PTR) {
                    GPAR(*z)->color = RED;
                }
                if(!rodou) {
                    PAR(*z)->color = BLACK;
                    right_rotate(T, (*z));
                } else {
                    right_rotate(T, (tmp));
                }
            }
        } else {
            y = GPAR(*z)->left;
            if(y->color == RED){
                PAR(*z)->color = BLACK;
                y->color = BLACK;
                GPAR(*z)->color = RED;
            } else {
                if((*z) == PAR(*z)->left) {
                    GPAR(*z)->color = RED;
                    tmp = PAR(*z);
                    PAR(*z) = PAR(*z)->parent;
                    (*z)->right->parent = tmp;
                    tmp->left = (*z)->right;
                    (*z)->right = tmp;
                    tmp->parent = (*z);
                    PAR(*z)->right = (*z);
                    tmp->parent = (*z);
                    rodou = 1;
                }

                if(GPAR(*z) != NIL_PTR) {
                    GPAR(*z)->color = RED;
                }
                if(!rodou) {
                    PAR(*z)->color = BLACK;
                    left_rotate(T, (*z));
                } else {
                    left_rotate(T, (tmp));
                }
            }
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
    Node* tmp = GPAR(x);
    GPAR(x) = GPAR(x)->parent;
    PAR(tmp)->right = PAR(x);
    tmp->right = PAR(x)->left;
    PAR(x)->left = tmp;
    tmp->parent = PAR(x);

    if(tmp == (*T)) {
        (*T) = PAR(x);
    }
	
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
    Node* tmp = GPAR(y);
    GPAR(y) = GPAR(y)->parent;
    PAR(tmp)->left = PAR(y);
    tmp->left = PAR(y)->right;
    PAR(y)->right = tmp;
    tmp->parent = PAR(y);


    if(tmp == (*T)) {
        (*T) = PAR(y);
    }

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
    if (r != NULL && r != NIL_PTR) {
        erd(r->left);
        printf("Key = %d - Color = %d\n", r->key, r->color);
        erd(r->right);
    }
}