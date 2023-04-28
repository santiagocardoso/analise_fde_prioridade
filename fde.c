#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fde.h"

int main(int argc, char **argv) {
    FILE *arquivo = fopen("dataset_v1.csv", "r");

    if (!arquivo) {
        printf("ERROR!\n");
        return 0;
    }

    Desc_movel *desc_movel = (Desc_movel*) malloc(sizeof(Desc_movel));
    inicializa_desc_movel(desc_movel);
    Desc *desc = (Desc*) malloc(sizeof(Desc));
    inicializa_desc(desc);

    le_arquivo(arquivo);


    fclose(arquivo);

    return 0;
}
