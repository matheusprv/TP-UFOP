#include <math.h>
#include "estruturas.h"
#include "ordenacao.h"

void gerarFitas(Fita * fitas);
void fecharArquivos(Fita * fitas);
bool todosMarcados(RegistroParaSubstituicao* registros);
void desmarcarRegistros(RegistroParaSubstituicao* registros);
void gerarSelecaoSubstituicao(Fita * fitas, InfoOrdenacao *infoOrdenacao);
void gerarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao);
void setPointeirosInicio(Fita * fitas);
Intercalacao * gerarFitasIntercalacao(int qtdFitas);
bool todosOsDadosLidos(Intercalacao * intercalacao, int qtdFitas);
void lerPrimeirosDados(int inicio, Intercalacao * fitasIntercalacao, Fita * fitas, int qtdFitas);
int procurarMenorValor(Intercalacao * dadosIntercalacao, int qtdFitas);
void intercalarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao);
void intercalacao_balanceada(InfoOrdenacao * infoOrdenacao);