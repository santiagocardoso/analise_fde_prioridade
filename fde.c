#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fde.h"

int main(int argc, char **argv) {
    FILE *arquivo = fopen("dataset_v1.csv", "r");

    if (!arquivo) {
        printf("ERROR!\n");
        return 0;
    }

    int opcao = -1;
    while (opcao != 0) {
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                Desc *desc = (Desc*) malloc(sizeof(Desc));
                inicializa_desc(desc);
                le_arquivo_desc(arquivo, desc);
                int opcao = -1;
                while (opcao != 0) {
                    menu_desc();
                    scanf("%d", &opcao);
                    switch (opcao) {
                        case 0:
                            printf("Retornando...\n");
                            break;
                        case 1:
                            imprime_fila_desc(desc);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                break;
            case 2:
                Desc_movel *desc_movel = (Desc_movel*) malloc(sizeof(Desc_movel));
                inicializa_desc_movel(desc_movel);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    fclose(arquivo);

    return 0;
}
