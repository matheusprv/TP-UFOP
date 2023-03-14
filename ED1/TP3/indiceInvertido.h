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
int consulta(IndiceInvertido, Chave*, int, NomeDocumento*, int *);
void imprimeIndiceInvertido(IndiceInvertido);
void imprimeDocumentos(NomeDocumento*, int);

void sort(NomeDocumento*, int);

void leEntrada(IndiceInvertido, int *);
void leOpcao(IndiceInvertido, int);
void executaBuscaDoUsuario(IndiceInvertido, int, char *);
void copiaPalavrasBuscadas(Chave *, int *, char *);

void merge(NomeDocumento*, int, int, int);
void mergeSort(NomeDocumento*, int, int);

void printColisoes();

#endif // !HASH_ABERTO
