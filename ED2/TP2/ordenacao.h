# ifndef ordenacao_h
# define ordenacao_h

#include "estruturas.h"

//HeapSort:

// faz a comparacao para ver se registro1 > registro2
int compare(RegistroParaSubstituicao registro1, RegistroParaSubstituicao t2);

//QuickSort Interno:

void trocarPosicao(TipoRegistro* registros, int * i, int * j);

void quicksort_interno(TipoRegistro * registros, int inicio, int fim);

void quicksort_interno_SelecaoSubs(RegistroParaSubstituicao * registros, int inicio, int fim);

#endif