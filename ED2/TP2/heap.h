# ifndef ordenacao_h
# define ordenacao_h

#include "estruturas.h"

// faz a comparacao utilizada para ordenar no heap sort
int compare(RegistroParaSubstituicao registro1, RegistroParaSubstituicao t2);

void heap_constroi(RegistroParaSubstituicao *v, int n);

void heap_refaz(RegistroParaSubstituicao *v, int esq, int dir);

void heap_sort(RegistroParaSubstituicao *v, int n);

#endif