#include <math.h>
#include "estruturas.h"
#include "ordenacao.h"

enum TipoFita {ENTRADA = 1, SAIDA = 2};

typedef struct{
    int n_blocos;
    FILE * arq;
    enum TipoFita tipo;
}Fita;

//para controlar as fitas de entrada durante o processo de intercalacao
typedef struct{
    int qtdItensLidos;
    TipoRegistro dadoLido;
    bool fitaAtiva;
}Intercalacao;

void trocaPosicao(TipoRegistro*, int *, int *);

void quicksort_interno(TipoRegistro *, int, int);

void gerarFitas(Fita *);

void fecharArquivos(Fita *);

bool todosMarcados(RegistroParaSubstituicao*);

void desmarcarRegistros(RegistroParaSubstituicao*);

void gerarSelecaoSubstituicao(Fita *, InfoOrdenacao *);

void gerarBlocos(Fita *, InfoOrdenacao *);

void intercalarBlocos(Fita *, InfoOrdenacao *);

Intercalacao * gerarFitasIntercalacao(int);