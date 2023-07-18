#include "estruturas.h"
#include <math.h>

typedef struct{
    int n_blocos;
    FILE * arq;
}Fita;


void trocaPosicao(TipoRegistro* registros, int * i, int * j);

void quicksort_interno(TipoRegistro * registros, int inicio, int fim);

void gerarFitas(Fita * fitas);

void fecharArquivos(Fita * fitas);

void gerarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao);

void intercalarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao);
