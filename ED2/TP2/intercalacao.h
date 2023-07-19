#include "estruturas.h"
#include <math.h>

typedef struct{
    int n_blocos;
    FILE * arq;
}Fita;

//para controlar as fitas de entrada durante o processo de intercalacao
typedef struct{
    int qtdItensLidos;
    TipoRegistro dadoLido;
}Intercalacao;

enum TipoFita {ENTRADA = 1, SAIDA = 2};

void trocaPosicao(TipoRegistro* registros, int * i, int * j);

void quicksort_interno(TipoRegistro * registros, int inicio, int fim);

void gerarFitas(Fita * fitas);

void fecharArquivos(Fita * fitas);

void gerarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao);

void intercalarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao);

Intercalacao * gerarFitasIntercalacao(int qtdFitas);