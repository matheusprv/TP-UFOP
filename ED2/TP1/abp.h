#ifndef ABP
#define ABP

#include "estruturas.h"

typedef struct{
    TipoRegistro item;
    long esq, dir;
}TipoItem;

void constroiArvore(char *file);
void atualizaPonteiros(FILE *arq, TipoItem *item);
bool pequisarAbp(FILE *arq, TipoRegistro *pesquisado);

#endif