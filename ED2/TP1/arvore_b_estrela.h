#ifndef ARVORE_B_ESTRELA
#define ARVORE_B_ESTRELA

#include "stdbool.h"
#include <stdio.h>

#define MM 2
#define MM2 4

typedef long TipoChave;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoRegistro{
    TipoChave Chave;
    long dado1;
    char dado2[1001];
    char dado3[5001];
} TipoRegistro;

typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPagina{ 
    TipoIntExt Pt; 
    union {
        struct { 
            int ni; 
            TipoChave ri[MM]; 
            TipoApontador pi[MM + 1];
        } U0; 
        struct { 
            int ne; 
            TipoRegistro re[MM2];
        } U1;
    } UU;
} TipoPagina;

bool Pesquisa(TipoRegistro *x, TipoApontador *Ap);

void Insere(TipoRegistro Reg, TipoApontador *Ap);

#endif