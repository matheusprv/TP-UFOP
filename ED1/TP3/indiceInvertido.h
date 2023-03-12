#ifndef HASH_ABERTO
#define HASH_ABERTO

#include "hash.h"

/* Os cabecalhos de todas as funcoes e os TADs podem ser alterados */

#define VAZIO " !!!!!!!!!!!!!!!!!!!!\0 "

typedef struct {
    int n; // numero de documentos
    Chave chave;
    NomeDocumento documentos[ND];
} Item;

typedef Item IndiceInvertido[M];

/* Funções */
void inicia(IndiceInvertido);
bool insereDocumento(IndiceInvertido, Chave, NomeDocumento);
int busca(IndiceInvertido, Chave);
int consulta(IndiceInvertido, Chave*, int, NomeDocumento*);
void imprime(IndiceInvertido);

void sort(NomeDocumento*, int);

void leEntrada(IndiceInvertido, int *);
void leOpcao(IndiceInvertido, char*);

void merge(NomeDocumento*, int, int, int);
void mergeSort(NomeDocumento*, int, int);

#endif // !HASH_ABERTO
