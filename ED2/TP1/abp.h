#ifndef ABP
#define ABP

#include "estruturas.h"
#include "cores.h"

typedef struct{
    TipoRegistro item;
    long esq, dir;
}TipoItem;

void constroiArvore(FILE *, FILE *, Resultados *);

void atualizaPonteiros(FILE *, TipoItem *, Resultados *);

bool pequisarAbp(FILE *, TipoRegistro *, Resultados *);

bool arvore_binaria_de_pesquisa(char *, Resultados *);
#endif