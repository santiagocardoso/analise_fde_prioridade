typedef struct info {
    char nome[20];
    char curso[20];
    int matricula;
    int rank;
} Info;

typedef struct no {
    Info *data;
    struct no *proximo;
    struct no *antes;
} No;

typedef struct desc {
    int tam;
    No *cauda;
    No *frente;
} Desc;

typedef struct desc_movel {
    int tam;
    No *cauda;
    No *frente;
    No *ref_movel;
} Desc_movel;

void menu();
void menu_desc();

void inicializa_desc(Desc *p);
void inicializa_desc_movel(Desc_movel *p);
No* inicializa_no(Info *info);

int rank(No *no);

void le_arquivo(FILE *arquivo, Desc *desc, Desc_movel *desc_movel);

void insere_na_fila_desc(No *no, Desc *desc);
void remover_da_fila_desc(Desc *desc);
void imprime_fila_desc(Desc *desc);

void insere_na_fila_desc_movel(No *no, Desc_movel *desc_movel);
void remover_da_fila_desc_movel(Desc_movel *desc_movel);
void imprime_fila_desc_movel(Desc_movel *desc_movel);