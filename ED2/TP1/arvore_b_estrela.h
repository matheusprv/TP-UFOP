#ifndef ARVORE_B_ESTRELA
#define ARVORE_B_ESTRELA

#include "estruturas.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include "cores.h"


void InsereNaPaginaExterna(TipoApontadorEstrela Ap, TipoRegistroEstrela Reg);

void InsereNaPaginaInterna(TipoApontadorEstrela Ap, TipoChave Reg, TipoApontadorEstrela ApDir);

void Ins_b_estrela(TipoRegistroEstrela Reg, TipoApontadorEstrela Ap, short *cresceu, TipoChave *RegRetorno, TipoApontadorEstrela *ApRetorno);

bool Pesquisa(TipoRegistroEstrela *x, TipoApontadorEstrela *Ap);

void Insere_b_estrela(TipoRegistroEstrela Reg, TipoApontadorEstrela *Ap);

void inicializa_b_estrela (TipoApontadorEstrela * Arvore);

bool arvore_b_estrela(long chave, char * nomeArquivo, int quantidade, Resultados * resultados);

void printaArvore(TipoApontadorEstrela Arvore, int level);

#endif