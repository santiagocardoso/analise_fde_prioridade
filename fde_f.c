#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fde.h"

void menu() {
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("           ANALISE DE DESEMPENHO\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Escolha uma opção:\n");
    printf("[0] Sair\n");
    printf("[1] Gerar FDE-Prioridade sem referencia movel\n");
    printf("[2] Gerar FDE-Prioridade com referencia movel\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

void menu_desc() {
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("          DESCRITOR SEM REF MOVEL\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Escolha uma opção:\n");
    printf("[0] Sair\n");
    printf("[1] Mostrar fila\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

void menu_desc_movel() {
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("          DESCRITOR COM REF MOVEL\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Escolha uma opção:\n");
    printf("[0] Sair\n");
    printf("[1] Mostrar fila\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

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
    novo->data = info;
    novo->proximo = NULL;
    novo->antes = NULL;
    return novo;
}

void le_arquivo_desc(FILE *arquivo, Desc *desc) {
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

        insere_na_fila_desc(no, desc);
    }
}

void insere_na_fila_desc(No *no, Desc *desc) {
    // descritor nomal
    if (!desc->cauda && !desc->frente) {
        desc->cauda = no;
        desc->frente = no;
        desc->tam_info++;
    }
    else {
        No *aux = desc->cauda;
        desc->cauda = no;
        no->proximo = aux;
        aux->antes = no;
        desc->tam_info++;
    }
}

void imprime_fila_desc(Desc *desc) {
    /*No *aux = desc->frente;
    while (aux) {
        printf("%s,%d,%d,%s\n", aux->data->nome, aux->data->matricula, aux->data->rank, aux->data->curso);
        aux = aux->antes;
    }*/
    No *aux = desc->cauda;
    while (aux) {
        printf("%s,%d,%d,%s\n", aux->data->nome, aux->data->matricula, aux->data->rank, aux->data->curso);
        aux = aux->proximo;
    }
}
