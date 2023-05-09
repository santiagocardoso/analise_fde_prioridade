#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fde.h"

void menu() {
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("   ANALISE DE DESEMPENHO\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Escolha uma opção:\n");
    printf("[0] Sair\n");
    printf("[1] Gerar FDE-Prioridade\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

void menu_desc() {
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("         DESCRITOR\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Escolha uma opção:\n");
    printf("[0] Sair\n");
    printf("[1] Mostrar fila\n");
    printf("[2] Remover da fila\n");
    printf("[3] Reiniciar fila\n");
    printf("[4] Mostrar fila movel\n");
    printf("[5] Remover da fila movel\n");
    printf("[6] Reiniciar fila movel\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
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

int rank(No *no) {
    return no->data->rank;
}

void cria_vetor_strings(FILE *arquivo, char strings[10002][50]) {
    char linha[50];
    fgets(linha, sizeof(linha), arquivo); // ignorar a primeira linha do arquivo
    int i = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(strings[i], linha);
        i++;
    }
    strings[i][0] = '\0';
}

void imprime(char strings[10002][50]) {
    int i = 0;
    while (strings[i][0] != '\0') {
        printf("%s", strings[i]);
        i++;
    }
}

void le_arquivo(char strings[10002][50], Desc *desc, Desc_movel *desc_movel) {
    int i = 0;
    while (strings[i][0] != '\0') {
        Info *info = (Info*) malloc(sizeof(Info));

        char nome[15];
        int matricula;
        int rank;
        char curso[15];
        sscanf(strings[i], "%[^,],%d,%d,%[^,\n]", nome, &matricula, &rank, curso);

        strcpy(info->nome, nome);
        info->matricula = matricula;
        info->rank = rank;
        strcpy(info->curso, curso);

        No *no1 = inicializa_no(info);
        No *no2 = inicializa_no(info);

        insere_na_fila_desc(no1, desc);
        insere_na_fila_desc_movel(no2, desc_movel);

        i++;
    }
}

// descritor sem referencia movel
void insere_na_fila_desc(No *no, Desc *desc) {
    if (!desc->cauda && !desc->frente) {
        desc->cauda = no;
        desc->frente = no;
    }
    else {
        No *aux = desc->cauda;
        
        while (aux && rank(aux) < rank(no))
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
    if (!desc->frente) {
        printf("Fila vazia!\n");
        return;
    }
    No *aux = desc->frente;
    desc->frente = desc->frente->antes;
    free(aux);
}

void imprime_fila_desc(Desc *desc) {
    if (!desc->frente) {
        printf("Fila vazia!\n");
        return;
    }
    No *aux = desc->frente;
    while (aux) {
        printf("%s,%d,%d,%s\n", aux->data->nome, aux->data->matricula, aux->data->rank, aux->data->curso);
        aux = aux->antes;
    }
}

void reiniciar_fila_desc(Desc *desc) {
    if (!desc->frente) {
        printf("Fila vazia!\n");
        return;
    }
    No *aux = desc->frente;
    while (aux) {
        desc->frente = aux->antes;
        free(aux);
        aux = desc->frente;
    }
    desc->frente = NULL;
}

// descritor com referencia movel
void insere_na_fila_desc_movel(No *no, Desc_movel *desc_movel) {
    if (!desc_movel->cauda && !desc_movel->frente) {
        desc_movel->cauda = no;
        desc_movel->frente = no;
        desc_movel->ref_movel = no;
    }
    else {
        if (rank(no) <= rank(desc_movel->cauda)) {
            no->proximo = desc_movel->cauda;
            desc_movel->cauda->antes = no;
            desc_movel->cauda = no;
        }
        else if (rank(no) > rank(desc_movel->frente)) {
            no->antes = desc_movel->frente;
            desc_movel->frente->proximo = no;
            desc_movel->frente = no;
        }
        else if (rank(desc_movel->cauda) < rank(no) <= rank(desc_movel->ref_movel)) {
            No *aux = desc_movel->cauda;
        
            while (aux && rank(aux) < rank(no))
                aux = aux->proximo;

            no->proximo = aux;
            no->antes = aux->antes;
            aux->antes->proximo = no;
            aux->antes = no;
        }
        else if (rank(desc_movel->ref_movel) < rank(no) <= rank(desc_movel->frente)) {
            No *aux = desc_movel->ref_movel;
        
            while (aux && rank(aux) < rank(no))
                aux = aux->proximo;
                
            no->proximo = aux;
            no->antes = aux->antes;
            aux->antes->proximo = no;
            aux->antes = no;
        }
    }

    desc_movel->tam++;
}

void remover_da_fila_desc_movel(Desc_movel *desc_movel) {
    if (!desc_movel->frente) {
        printf("Fila vazia!\n");
        return;
    }
    No *aux = desc_movel->frente;
    desc_movel->frente = desc_movel->frente->antes;
    desc_movel->ref_movel = desc_movel->frente;
    free(aux);
}

void imprime_fila_desc_movel(Desc_movel *desc_movel) {
    if (!desc_movel->frente) {
        printf("Fila vazia!\n");
        return;
    }
    No *aux = desc_movel->frente;
    while (aux) {
        printf("%s,%d,%d,%s\n", aux->data->nome, aux->data->matricula, aux->data->rank, aux->data->curso);
        aux = aux->antes;
    }
}

void reiniciar_fila_desc_movel(Desc_movel *desc_movel) {
    if (!desc_movel->frente) {
        printf("Fila vazia!\n");
        return;
    }
    No *aux = desc_movel->frente;
    while (aux) {
        desc_movel->frente = aux->antes;
        free(aux);
        aux = desc_movel->frente;
    }
    desc_movel->frente = NULL;
}
