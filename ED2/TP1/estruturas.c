#include "estruturas.h"

//Comecando com -2 para a inicializacao da variavel e para a leitura do valor
long transferenciasPreProcessamento(){
    static long int qtdTransferencias = -2;
    qtdTransferencias++;
    return qtdTransferencias;
}

long comparacoesPreProcessamento(){
    static long int qtdComparacoes = -2;
    qtdComparacoes++;
    return qtdComparacoes;
}

long transferenciasPesquisa(){
    static long int qtdTransferencias = -2;
    qtdTransferencias++;
    return qtdTransferencias;
}

long comparacoesPesquisa(){
    static long int qtdComparacoes = -2;
    qtdComparacoes++;
    return qtdComparacoes;
}