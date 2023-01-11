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

double calcularDeslocamentoParcial(Ponto, Ponto);

void calcularDeslocamento(Trajeto*, int, int);

void ordena();

void imprime(Trajeto * trajetos, int qtdTrajetos);

Trajeto* alocaTrajetos(int n);

void lerTrajetos(int, int, Trajeto*);

Trajeto getTrajeto(Trajeto* trajetos, int index);

#endif