#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

typedef struct avlNode {
    Aluno *info;
    int fatbal;
    struct avlNode *esq;
    struct avlNode *dir;
} AVLNode;

struct avlTree {
    AVLNode *raiz;
    int status;
};

//              Fila
typedef struct queueNode {
    AVLNode *info;
    struct queueNode *prox;
} QueueNode;

typedef struct queue {
    QueueNode *inicio;
    QueueNode *fim;
} Queue;

static void inicializarFila(Queue *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

static int filaVazia(Queue *f) {
    return f->inicio == NULL;
}

static void enQueue(Queue *f, AVLNode *valor) {
    QueueNode *novo = (QueueNode*) malloc(sizeof(QueueNode));
    novo->info = valor;
    novo->prox = NULL;
    if (filaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

static AVLNode* deQueue(Queue *f) {
    QueueNode *aux = f->inicio;
    AVLNode *valor = aux->info;
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) f->fim = NULL;
    free(aux);
    return valor;
}

//              Nó

static AVLNode* criarNo(Aluno elem) {
    AVLNode *novo = (AVLNode*) malloc(sizeof(AVLNode));
    novo->info = (Aluno*) malloc(sizeof(Aluno));
    *(novo->info) = elem;

    novo->fatbal = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

static void rotacaoDir(AVLNode **a, int *cresceu) {
    AVLNode *b, *c;
    b = (*a)->esq;
    if (b->fatbal == -1) { // rotação simples à direita
        (*a)->esq = b->dir;
        b->dir = *a;
        (*a)->fatbal = 0;
        *a = b;
    } else { // rotação dupla à direita
        c = b->dir;
        b->dir = c->esq;
        c->esq = b;
        (*a)->esq = c->dir;
        c->dir = *a;
        if (c->fatbal == -1) (*a)->fatbal = 1; else (*a)->fatbal = 0;
        if (c->fatbal == 1)  b->fatbal = -1;  else b->fatbal = 0;
        *a = c;
    }
    (*a)->fatbal = 0;
    *cresceu = 0;
}

static void rotacaoEsq(AVLNode **a, int *cresceu) {
    AVLNode *b, *c;
    b = (*a)->dir;
    if (b->fatbal == 1) { // rotação simples à esquerda
        (*a)->dir = b->esq;
        b->esq = *a;
        (*a)->fatbal = 0;
        *a = b;
    } else { // rotação dupla à esquerda
        c = b->esq;
        b->esq = c->dir;
        c->dir = b;
        (*a)->dir = c->esq;
        c->esq = *a;
        if (c->fatbal == 1)  (*a)->fatbal = -1; else (*a)->fatbal = 0;
        if (c->fatbal == -1) b->fatbal = 1;    else b->fatbal = 0;
        *a = c;
    }
    (*a)->fatbal = 0;
    *cresceu = 0;
}

static int inserirNo(AVLNode **raiz, Aluno elem, int *cresceu) {
    if (*raiz == NULL) {
        *raiz = criarNo(elem);
        *cresceu = 1;
        return 1;
    }

    int cmp = strcmp(elem.matr, (*raiz)->info->matr);
    if (cmp == 0) {
        *cresceu = 0;
        return 0;
    }

    int inserido;
    if (cmp < 0) {
        inserido = inserirNo(&((*raiz)->esq), elem, cresceu);
        if (inserido && *cresceu) {
            switch ((*raiz)->fatbal) {
                case 1:  (*raiz)->fatbal = 0; *cresceu = 0; break;
                case 0:  (*raiz)->fatbal = -1; break;
                case -1: rotacaoDir(raiz, cresceu); break;
            }
        }
    } else {
        inserido = inserirNo(&((*raiz)->dir), elem, cresceu);
        if (inserido && *cresceu) {
            switch ((*raiz)->fatbal) {
                case -1: (*raiz)->fatbal = 0; *cresceu = 0; break;
                case 0:  (*raiz)->fatbal = 1; break;
                case 1:  rotacaoEsq(raiz, cresceu); break;
            }
        }
    }
    return inserido;
}

static AVLNode* buscarNo(AVLNode *raiz, char *matr) {
    if (raiz == NULL) return NULL;
    int cmp = strcmp(matr, raiz->info->matr);
    if (cmp == 0) return raiz;
    else if (cmp < 0) return buscarNo(raiz->esq, matr);
    else return buscarNo(raiz->dir, matr);
}

static void emOrdemNo(AVLNode *raiz) {
    if (raiz != NULL) {
        emOrdemNo(raiz->esq);
        aluno_exibir(*(raiz->info));
        printf("--\n");
        emOrdemNo(raiz->dir);
    }
}

static void destroyNo(AVLNode *raiz) {
    if (raiz != NULL) {
        destroyNo(raiz->esq);
        destroyNo(raiz->dir);
        free(raiz->info);
        free(raiz);
    }
}

/*"Interface" avl*/

AVLTree* avl_criar(void) {
    AVLTree *arvore = (AVLTree*) malloc(sizeof(AVLTree));
    arvore->raiz = NULL;
    arvore->status = 0;
    return arvore;
}

void avl_destruir(AVLTree *arvore) {
    if (arvore == NULL) return;
    destroyNo(arvore->raiz);
    free(arvore);
}

int avl_cadastrar(AVLTree *arvore, Aluno elem) {
    int cresceu = 0;
    return inserirNo(&(arvore->raiz), elem, &cresceu);
}

Aluno* avl_buscar(AVLTree *arvore, char *matr) {
    AVLNode *no = buscarNo(arvore->raiz, matr);
    if (no != NULL) return no->info;
    else return NULL;

}

void avl_percorrerPorNivel(AVLTree *arvore) {
    if (arvore->raiz == NULL) {
        printf("Arvore vazia!\n");
        return;
    }
    Queue fila;
    AVLNode *aux;
    inicializarFila(&fila);
    enQueue(&fila, arvore->raiz);
    while (!filaVazia(&fila)) {
        aux = deQueue(&fila);
        printf("Nome: %s | Matricula: %s | Media: %.2f | Faltas: %d | FatBal: %d\n",
               aux->info->nome, aux->info->matr, aux->info->media, aux->info->faltas, aux->fatbal);
        if (aux->esq != NULL) enQueue(&fila, aux->esq);
        if (aux->dir != NULL) enQueue(&fila, aux->dir);
    }
}

void avl_percorrerEmOrdem(AVLTree *arvore) {
    if (arvore->raiz == NULL) printf("Arvore vazia\n"); 
    else emOrdemNo(arvore->raiz);
}