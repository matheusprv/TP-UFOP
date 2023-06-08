#ifndef ACESSO_INDEXADO_H
#define ACESSO_INDEXADO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estruturas.h"

#define ITENSPAGINA 10
#define MAXTABELA 101

//definicao de uma entrada da tabela de indice das paginas
typedef struct{
    long chave;
} tipoindice;

//definicao de um item do arquivo de dados
typedef TipoRegistro tipoitem;

bool pesquisa(tipoindice *tab, int tam, TipoChave Chave, FILE *file);
void acessoIndexado(TipoChave chave, char *file);
bool pesquisaBinaria(tipoitem *pagina, TipoChave chave, TipoRegistro *item);

#endif