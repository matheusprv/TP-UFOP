#ifndef ARVORE_B_ESTRELA
#define ARVORE_B_ESTRELA

#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>

#define M 256
#define MM 2*M

#define M2 512
#define MM2 2*M2

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

void InsereNaPaginaExterna(TipoApontador Ap, TipoRegistro Reg);

void InsereNaPaginaInterna(TipoApontador Ap, TipoChave Reg, TipoApontador ApDir);

void Ins_b_estrela(TipoRegistro Reg, TipoApontador Ap, short *cresceu, TipoChave *RegRetorno, TipoApontador *ApRetorno);

bool Pesquisa(TipoRegistro *x, TipoApontador *Ap);

void Insere_b_estrela(TipoRegistro Reg, TipoApontador *Ap);

void inicializa_b_estrela (TipoApontador * Arvore);



#endif