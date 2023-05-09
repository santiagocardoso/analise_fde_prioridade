#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fde.h"

int main(int argc, char **argv) {
    int casos = 500;

    FILE *arquivo = fopen("dataset_v1.csv", "r");

    if (!arquivo) {
        printf("ERROR!\n");
        return 0;
    }

    char strings[10002][50];
    cria_vetor_strings(arquivo, strings);
    // imprime(strings);
    
    int opcao = -1;
    while (opcao != 0 && casos <= 9000) {
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                FILE *arquivo = fopen("dataset_v1.csv", "r");

                if (!arquivo) {
                    printf("ERROR!\n");
                    return 0;
                }

                char strings[10002][50];
                cria_vetor_strings(arquivo, strings);
                randomize(strings);
                // imprime(strings);

                Desc *desc = (Desc*) malloc(sizeof(Desc));
                inicializa_desc(desc);

                Desc_movel *desc_movel = (Desc_movel*) malloc(sizeof(Desc_movel));
                inicializa_desc_movel(desc_movel);

                le_arquivo(strings, desc, desc_movel, casos);

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
                            reiniciar_fila_desc(desc);
                            break;
                        case 4:
                            imprime_fila_desc_movel(desc_movel);
                            break;
                        case 5:
                            remover_da_fila_desc_movel(desc_movel);
                            break;
                        case 6:
                            reiniciar_fila_desc_movel(desc_movel);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                free(desc);
                free(desc_movel);
                fclose(arquivo);
                casos += 500;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    return 0;
}
