typedef struct aluno {
    char matr[20];
    char nome[100];
    int faltas;
    float media;
} Aluno;

Aluno aluno_criar(char *matr, char *nome, float media, int faltas);

void aluno_exibir(Aluno aluno);