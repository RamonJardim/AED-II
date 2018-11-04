#include "rb_tree.h"

/* Valor de sentinela, indica que chegamos em alguma folha ou entao
 a raiz da arvore */
Node NIL_NODE = {.key = 213980,
                 .color = BLACK/*,
                 .left = &NIL_NODE,
                 .right = &NIL_NODE*/};

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
        (*T)->color = BLACK;
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
            y = GPAR(*z)->right; // nil
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
                if(GPAR(*z) != NIL_PTR) {
                    GPAR(*z)->color = RED;
                }////////////////////////////////////////
                right_rotate(T, (*z));
            }
        } else {
            y = GPAR(*z)->left;
            if(y->color == RED){
                PAR(*z)->color = BLACK;
                y->color = BLACK;
                GPAR(*z)->color = RED;
            } else {
                if((*z) == PAR(*z)->left) {
                    (*z) = PAR(*z);
                    right_rotate(T, (*z));
                }
                PAR(*z)->color = BLACK;
                GPAR(*z)->color = RED;
                left_rotate(T, (*z));
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
    
    
    /*Node* y = x->right;
    Node* b = y->left;

    if(PAR(x)->right == x){
        PAR(x)->right = y;
    } else {
        PAR(x)->left = y;
    }

    y->parent = x->parent;
    x->parent = y;
    x->right = b;
    b->parent = x;
    y->left = x;*/
	Node *node, *tmp;
	
	node = x;
	tmp = node->right;
	
	//printf("[No desbalanceado: %d]\n[Rotacao: SE]\n[x=%d y=%d z=%d]\n", node->RA, node->RA, node->pRight->RA, node->pRight->pRight->RA);
	
	node->right = tmp->left;
	tmp->left = node;
	
	//updateHeight(node);
	x = tmp;
	
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
    /*Node* x = y->left; //nil
    Node* b = x->right; //NULL

    if(PAR(y)->right == y){
        PAR(y)->right = x;
    } else {
        PAR(y)->left = x;
    }

    if(x != NIL_PTR) {
        x->parent = y->parent;
    }
    y->parent = x;
    y->left = b ? b : NIL_PTR;
    b->parent = y;
    x->right = y;*/

    Node* tmp;
    tmp = y->right;
    /* Turn y's left sub-tree into x's right sub-tree */
    y->right = tmp->left;
    if ( tmp->left != NULL )
        tmp->left->parent = y;
    /* y's new parent was x's parent */
    tmp->parent = y->parent;
    /* Set the parent to point to y instead of x */
    /* First see whether we're at the root */
    if ( y->parent == NULL ) (*T) = y;
    else
        if ( y == (y->parent)->left )
            /* x was on the left of its parent */
            y->parent->left = tmp;
        else
            /* x must have been on the right */
            y->parent->right = tmp;
    /* Finally, put x on y's left */
    tmp->left = y;
    y->parent = tmp;
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
    if (r != NIL_PTR) {
        erd(r->left);
        printf("%d - %d\n", r->key, r->color);
        erd(r->right);
    }
}