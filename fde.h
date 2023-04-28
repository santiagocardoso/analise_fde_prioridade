typedef struct info {
    char *nome;
    char *curso;
    int matricula;
    int rank;
} Info;

typedef struct no {
    Info data;
    struct no *proximo;
} No;

typedef struct desc_movel {
    int tam_lista;
    int tam_info;
    No *cauda;
    No *frente;
    No *ref_movel;
} Desc_movel;

typedef struct desc {
    int tam_info;
    No *cauda;
    No *frente;
} Desc;

void inicializa_desc(Desc *p);
void inicializa_desc_movel(Desc_movel *p);
No* inicializa_no(Info *info);
void le_arquivo(FILE *arquivo);
