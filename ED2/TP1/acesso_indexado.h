#ifndef ACESSO_INDEXADO_H
#define ACESSO_INDEXADO_H

#include "estruturas.h"

#define ITENSPAGINA 10
#define MAXTABELA 1000

//definicao de uma entrada da tabela de indice das paginas
typedef struct{
    long chave;
} Indice;


bool pesquisa(Indice *tab, int tam, TipoChave Chave, FILE *arq, TipoRegistro * resultado);
bool pesquisaBinaria(TipoRegistro *pagina, TipoChave chave, TipoRegistro *item);

int geraTabela(Indice * tabela, FILE ** arq, char *nomeArquivo);

bool acessoIndexado(TipoChave chave, char *nomeArquivo, TipoRegistro * pesquisar);

#endif