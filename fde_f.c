#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fde.h"

void inicializa_desc(Desc *p) {
    p->tam_info = 0;
    p->cauda = NULL;
    p->frente = NULL;
}

void inicializa_desc_movel(Desc_movel *p) {
    p->tam_info = 0;
    p->tam_lista = 0;
    p->cauda = NULL;
    p->frente = NULL;
    p->ref_movel = NULL;
}

No* inicializa_no(Info *info) {
    No *novo = (No*) malloc(sizeof(No));
    novo->data = *info;
    novo->proximo = NULL;
    return novo;
}

void le_arquivo(FILE *arquivo) {
    char linha[256];
    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo)) {
        Info *info = (Info*) malloc(sizeof(Info));

        char *nome = (char*) malloc(30);
        int matricula;
        int rank;
        char *curso = (char*) malloc(30);
        sscanf(linha, " %[^,],%d,%d, %[^'\n']", nome, &matricula, &rank, curso);

        info->nome = nome;
        info->matricula = matricula;
        info->rank = rank;
        info->curso = curso;

        free(nome);
        free(curso);
        matricula = 0;
        rank = 0;

        No *no = inicializa_no(info);
    }
}
