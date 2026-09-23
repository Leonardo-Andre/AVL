#include <stdio.h>
#include <string.h>
#include "aluno.h"

Aluno aluno_criar(char *matr, char *nome, float media, int faltas) {
    Aluno aluno;
    strncpy(aluno.matr, matr, sizeof(aluno.matr) - 1);
    aluno.matr[sizeof(aluno.matr) - 1] = '\0';
    strncpy(aluno.nome, nome, sizeof(aluno.nome) - 1);
    aluno.nome[sizeof(aluno.nome) - 1] = '\0';
    aluno.media = media;
    aluno.faltas = faltas;
    return aluno;
}

void aluno_exibir(Aluno aluno) {
    printf("Nome: %s\n", aluno.nome);
    printf("Matricula: %s\n", aluno.matr);
    printf("Media: %.2f\n", aluno.media);
    printf("Faltas: %d\n", aluno.faltas);
}