#ifndef HASH_ABERTO
#define HASH_ABERTO

#include "hash.h"

/* Os cabeçalhos de todas as funções e os TADs podem ser alterados */

#define VAZIO " !!!!!!!!!!!!!!!!!!!!\0 "

typedef struct {
    int n; // numero de documentos
    Chave chave;
    NomeDocumento documentos[ND];
} Item;

typedef Item IndiceInvertido[M];

/* Funções */



void inicia(IndiceInvertido);
bool insereDocumento(IndiceInvertido, Item, NomeDocumento, int);
int busca(IndiceInvertido, Chave, int);
int consulta(IndiceInvertido, Chave*, int, NomeDocumento*);
void imprime(IndiceInvertido);

void sort(NomeDocumento*, int);

#endif // !HASH_ABERTO
