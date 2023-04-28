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
void menu_desc_movel();

void inicializa_desc(Desc *p);
No* inicializa_no(Info *info);
void insere_na_fila_desc(No *no, Desc *desc);
void imprime_fila_desc(Desc *desc);

void inicializa_desc_movel(Desc_movel *p);

void le_arquivo_desc(FILE *arquivo, Desc *desc, Desc_movel *desc_movel);