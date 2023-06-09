#ifndef ARVORE_B_H
#define ARVORE_B_H

#include <stdio.h>
#include <stdbool.h>

#include "estruturas.h"

void inicializa(TipoApontador);

void pesquisa_arvore_b (TipoRegistro *, TipoApontador);

void imprime (TipoApontador);

void InsereNaPagina (TipoApontador, TipoRegistro, TipoApontador);

void Ins(TipoRegistro, TipoApontador, short *, TipoRegistro *, TipoApontador *);

void Insere(TipoRegistro, TipoApontador *);

#endif