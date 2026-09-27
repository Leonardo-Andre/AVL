#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "avl.h"

static void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void removerQuebraLinha(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

static void lerCampoTexto(char *rotulo, char *destino, size_t tamanho) {
    char buffer[tamanho + 1];
    int valido = 0;

    do {
        printf("%s (max %zu caracteres): ", rotulo, tamanho - 1);
        fgets(buffer, sizeof(buffer), stdin);

        if (strchr(buffer, '\n') == NULL) {
            limparBufferEntrada();
            printf("Texto muito longo (max %zu caracteres). Tente novamente.\n", tamanho - 1);
            continue;
        }

        removerQuebraLinha(buffer);

        if (strlen(buffer) == 0) printf("Campo nao pode ficar vazio. Tente novamente.\n");
        else {
            strcpy(destino, buffer);
            valido = 1;
        }
    } while (!valido);
}

static void exibirMenu(void) {
    printf("\n--- Menu ---\n");
    printf("1 - Cadastrar aluno\n");
    printf("2 - Buscar aluno por matricula\n");
    printf("3 - Percorrer por nivel (com fator de balanceamento)\n");
    printf("4 - Percorrer em ordem\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

int main(void) {
    AVLTree *arvore = avl_criar();
    int op;
    char matr[20], nome[100], matrBusca[20];
    float media;
    int faltas;
    Aluno *encontrado;

    do {
        exibirMenu();
        scanf("%d", &op);
        limparBufferEntrada();

        switch (op) {
            case 1:
                lerCampoTexto("Matricula", matr, sizeof(matr));
                lerCampoTexto("Nome", nome, sizeof(nome));

                printf("Media: ");
                scanf("%f", &media);
                limparBufferEntrada();

                printf("Faltas: ");
                scanf("%d", &faltas);
                limparBufferEntrada();

                if (!avl_cadastrar(arvore, aluno_criar(matr, nome, media, faltas))) {
                    printf("Matricula ja cadastrada!\n");
                }
                break;

            case 2:
                lerCampoTexto("Matricula a buscar", matrBusca, sizeof(matrBusca));
                encontrado = avl_buscar(arvore, matrBusca);
                if (encontrado != NULL) aluno_exibir(*encontrado);
                else printf("Aluno nao encontrado!\n");
                break;

            case 3:
                avl_percorrerPorNivel(arvore);
                break;

            case 4:
                avl_percorrerEmOrdem(arvore);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (op != 0);

    avl_destruir(arvore);
    return 0;
}