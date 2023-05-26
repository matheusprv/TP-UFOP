#ifndef ACESSO_INDEXADO_H
#define ACESSO_INDEXADO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ITENSPAGINA 4
#define MAXTABELA 100

//definicao de uma entrada da tabela de indice das paginas
typedef struct{
    int posicao;
    int chave;
} tipoindice;

//definicao de um item do arquivo de dados
typedef struct{
    char titulo[31]; 
    int chave; 
    float preco;
} tipoitem;

int pesquisa(tipoindice*, int, tipoitem*, FILE *);

#endif