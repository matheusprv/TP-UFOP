#ifndef ORDENACAO_C
#define ORDENACAO_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct ponto Ponto;

typedef struct trajeto Trajeto;

Ponto* alocaPontos(int n);

void desalocaPontos(Ponto*);

void desalocaTrajeto(Trajeto**, int, int);

void calcularDistancia(Trajeto*, int, int);

float calcularDeslocamentoParcial(Ponto, Ponto);

void calcularDeslocamento(Trajeto*, int, int);

void imprime(Trajeto * trajetos, int qtdTrajetos);

Trajeto* alocaTrajetos(int n);

void lerTrajetos(int, int, Trajeto*);

void ordenaDistancia(Trajeto*, int, int);

void ordenaDeslocamento(Trajeto*, int, int);

void ordenaNome(Trajeto*, int, int);

void ordernacao(Trajeto *, int);

#endif