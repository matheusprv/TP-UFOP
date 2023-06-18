#ifndef MENUS_H
#define MENUS_H

#include "acesso_indexado.h"
#include "abp.h"
#include "arvore_b.h"

bool verificaInputsValidos(int metodo, int quantidade, int situacao);

char * verificaSituacao(int situacao);

char * geraNomeArquivo(char * quantidade, int situacao, char * nomeArquivo);

long converteChave(char * chaveStr);

void selecionaMetodo(int metodo, long chave, char * nomeArquivo, int quantidade);

#endif