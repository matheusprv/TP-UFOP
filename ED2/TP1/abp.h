#ifndef ABP
#define ABP

#include "estruturas.h"
#include "cores.h"

typedef struct{
    TipoRegistro item;
    long esq, dir;
}TipoItem;

void constroiArvore(FILE * arq, FILE *arqAbp);

void atualizaPonteiros(FILE *arq, TipoItem *item);

bool pequisarAbp(FILE *arq, TipoRegistro *pesquisado);

bool arvore_binaria_de_pesquisa(char * nomeArquivo, Resultados * resultados);
#endif