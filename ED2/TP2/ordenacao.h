# ifndef ordenacao_h
# define ordenacao_h

#include "estruturas.h"

//HeapSort:

// faz a comparacao utilizada para ordenar no heap sort
int compare(RegistroParaSubstituicao registro1, RegistroParaSubstituicao t2);

void heap_constroi(RegistroParaSubstituicao *v, int n);

void heap_refaz(RegistroParaSubstituicao *v, int esq, int dir);

void heap_sort(RegistroParaSubstituicao *v, int n);

//QuickSort Interno:

void trocarPosicao(TipoRegistro* registros, int * i, int * j);

void quicksort_interno(TipoRegistro * registros, int inicio, int fim);

#endif