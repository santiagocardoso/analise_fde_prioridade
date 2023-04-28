#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fde.h"

void menu() {
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("           ANALISE DE DESEMPENHO\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Escolha uma opção:\n");
    printf("[0] Sair\n");
    printf("[1] Gerar FDE-Prioridade s/n referencia movel\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

void menu_desc() {
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("          DESCRITOR SEM REF MOVEL\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Escolha uma opção:\n");
    printf("[0] Sair\n");
    printf("[1] Mostrar fila\n");
    printf("[2] Remover da fila\n");
    printf("[3] Reiniciar fila\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

void menu_desc_movel() {
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("          DESCRITOR COM REF MOVEL\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Escolha uma opção:\n");
    printf("[0] Sair\n");
    printf("[1] Mostrar fila\n");
    printf("[2] Remover da fila\n");
    printf("[3] Reiniciar fila\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

void inicializa_desc(Desc *p) {
    p->tam = 0;
    p->cauda = NULL;
    p->frente = NULL;
}

void inicializa_desc_movel(Desc_movel *p) {
    p->tam = 0;
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

void le_arquivo_desc(FILE *arquivo, Desc *desc, Desc_movel *desc_movel) {
    char linha[256];
    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo)) {
        Info *info = (Info*) malloc(sizeof(Info));

        char *nome = (char*) malloc(30);
        int matricula;
        int rank;
        char *curso = (char*) malloc(30);
        sscanf(linha, " %[^,],%d,%d, %[^'\n']", nome, &matricula, &rank, curso);

        strcpy(info->nome, nome);
        info->matricula = matricula;
        info->rank = rank;
        strcpy(info->curso, curso);

        free(nome);
        free(curso);

        No *no = inicializa_no(info);

        insere_na_fila_desc(no, desc);
    }
}

void insere_na_fila_desc(No *no, Desc *desc) {
    if (!desc->cauda && !desc->frente) {
        desc->cauda = no;
        desc->frente = no;
    }
    else {
        No *aux = desc->cauda;
        
        while (aux && aux->data->rank < no->data->rank)
            aux = aux->proximo;

        if (!aux) {
            no->antes = desc->frente;
            desc->frente->proximo = no;
            desc->frente = no;
        }
        else if (!aux->antes) {
            no->proximo = aux;
            aux->antes = no;
            desc->cauda = no;
        }
        else {
            no->proximo = aux;
            no->antes = aux->antes;
            aux->antes->proximo = no;
            aux->antes = no;
        }
    }

    desc->tam++;
}

void remover_da_fila_desc(Desc *desc) {
    No *aux = desc->frente;
    desc->frente = desc->frente->antes;
    free(aux);
}

void reiniciar_fila_desc(Desc *desc) {
    No *aux = desc->frente;
    while (aux) {
        desc->frente = desc->frente->antes;
        free(aux);
        aux = desc->frente;
    }
}

void imprime_fila_desc(Desc *desc) {
    No *aux = desc->frente;
    while (aux) {
        printf("%s,%d,%d,%s\n", aux->data->nome, aux->data->matricula, aux->data->rank, aux->data->curso);
        aux = aux->antes;
    }
    /*No *aux = desc->cauda;
    while (aux) {
        printf("%s,%d,%d,%s\n", aux->data->nome, aux->data->matricula, aux->data->rank, aux->data->curso);
        aux = aux->proximo;
    }*/
}
