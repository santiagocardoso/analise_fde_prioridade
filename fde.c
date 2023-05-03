#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fde.h"

int main(int argc, char **argv) {
    int opcao = -1;
    while (opcao != 0) {
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                FILE *arquivo1 = fopen("dataset_v1.csv", "r");

                if (!arquivo1) {
                    printf("ERROR!\n");
                    return 0;
                }

                FILE *arquivo2 = fopen("dataset_v1.csv", "r");

                if (!arquivo2) {
                    printf("ERROR!\n");
                    return 0;
                }

                Desc *desc = (Desc*) malloc(sizeof(Desc));
                inicializa_desc(desc);

                Desc_movel *desc_movel = (Desc_movel*) malloc(sizeof(Desc_movel));
                inicializa_desc_movel(desc_movel);

                le_arquivo_desc(arquivo1, desc);
                le_arquivo_desc_movel(arquivo2, desc_movel);

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
                        case 2:
                            remover_da_fila_desc(desc);
                            break;
                        case 3:
                            imprime_fila_desc_movel(desc_movel);
                            break;
                        case 4:
                            remover_da_fila_desc_movel(desc_movel);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                free(desc);
                free(desc_movel);
                fclose(arquivo1);
                fclose(arquivo2);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    return 0;
}
