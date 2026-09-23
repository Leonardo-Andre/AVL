#include "aluno.h"

typedef struct avlTree AVLTree;

AVLTree* avl_criar(void);

void avl_destruir(AVLTree *arvore);

int avl_cadastrar(AVLTree *arvore, Aluno elem);

Aluno* avl_buscar(AVLTree *arvore, char *matr);

void avl_percorrerPorNivel(AVLTree *arvore);

void avl_percorrerEmOrdem(AVLTree *arvore);