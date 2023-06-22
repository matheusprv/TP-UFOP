#ifndef ARVORE_B_ESTRELA
#define ARVORE_B_ESTRELA

#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include "cores.h"

#define MB 2
#define MMB 2*MB

#define MB2 2
#define MMB2 2*MB2

typedef long TipoChave;

typedef struct TipoPaginaEstrela* TipoApontadorEstrela;

typedef struct TipoRegistroEstrela{
    TipoChave Chave;
    long dado1;
    char dado2[1001];
    char dado3[5001];
} TipoRegistroEstrela;

typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPaginaEstrela{ 
    TipoIntExt Pt; 
    union {
        struct { 
            int ni; 
            TipoChave ri[MMB]; 
            TipoApontadorEstrela pi[MMB + 1];
        } U0; 
        struct { 
            int ne; 
            TipoRegistroEstrela re[MMB2];
        } U1;
    } UU;
} TipoPaginaEstrela;

void InsereNaPaginaExterna(TipoApontadorEstrela Ap, TipoRegistroEstrela Reg);

void InsereNaPaginaInterna(TipoApontadorEstrela Ap, TipoChave Reg, TipoApontadorEstrela ApDir);

void Ins_b_estrela(TipoRegistroEstrela Reg, TipoApontadorEstrela Ap, short *cresceu, TipoChave *RegRetorno, TipoApontadorEstrela *ApRetorno);

bool Pesquisa(TipoRegistroEstrela *x, TipoApontadorEstrela *Ap);

void Insere_b_estrela(TipoRegistroEstrela Reg, TipoApontadorEstrela *Ap);

void inicializa_b_estrela (TipoApontadorEstrela * Arvore);

void arvore_b_estrela(long chave, char * nomeArquivo, int quantidade);

void printaArvore(TipoApontadorEstrela Arvore);

#endif