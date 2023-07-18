#include "intercalacao.h"

void trocarPosicao(TipoRegistro* registros, int * i, int * j){
    TipoRegistro auxiliar;

    auxiliar = registros[*i];
    registros[*i] = registros[*j];
    registros[*j] = auxiliar;
    *i += 1;
    *j -= 1;

}

void quicksort_interno(TipoRegistro * registros, int inicio, int fim){
    int i, j;
    TipoRegistro pivo; 

    i = inicio;
    j = fim;
    pivo = registros[(inicio + fim) / 2];

    while (i <= j){
        while (registros[i].nota < pivo.nota && i < fim)
            i++;
        
        while (registros[j].nota > pivo.nota && j > inicio)
            j--;

        if (i <= j)
            trocarPosicao(registros, &i, &j);
    }

    if (j > inicio)
        quicksort_interno(registros, inicio, j);

    if (i < fim)
        quicksort_interno(registros, i, fim);
}

void gerarFitas(Fita * fitas){
    for(int i = 0; i < 40; i++){
        fitas[i].n_blocos = 0;

        char arquivo[50];
        sprintf(arquivo, "fita_%d.bin", i+1);
        fitas[i].arq = fopen(arquivo, "wb");
    }
}

void fecharArquivos(Fita * fitas){
    for(int i = 0; i < 40; i++){
        fclose(fitas[i].arq);
    }
}

void gerarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao){

    FILE * arq = fopen("PROVAO_ALEATORIO.bin", "rb");
    TipoRegistro registrosInterno [20]; //Memoria Interna

    //Verificando a quantidade de blocos que serão lidos
    int qtdBlocos = (int) ceil(infoOrdenacao->quantidade / 20.0);
    int qtdItensALer, qtdItensQueFaltam = infoOrdenacao->quantidade;

    for(int i = 0; i < qtdBlocos; i++){
        //Verificando se a quantidade de itens a ser lido eh menor que 20, se for, ler somente a quantidade que falta
        qtdItensALer = qtdItensQueFaltam >= 20 ? 20 : qtdItensQueFaltam;
        qtdItensQueFaltam -= qtdItensALer;
        
        //Lendo os dados, salvando na estrutura interna e ordenando pela nota
        fread(registrosInterno, sizeof(TipoRegistro), qtdItensALer, arq);
        quicksort_interno(registrosInterno, 0, qtdItensALer-1);

        //Escrevendo o dado na fita
        fitas[i%20].n_blocos += 1;
        fwrite(registrosInterno, sizeof(TipoRegistro), qtdItensALer, fitas[i%20].arq);

        
    }
}

void intercalarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao){

}

void intercalacao_balanceada(InfoOrdenacao * infoOrdenacao){
    
    Fita fitas[40];
    gerarFitas(fitas);

    gerarBlocos(fitas, infoOrdenacao);

    intercalarBlocos(fitas, infoOrdenacao);


    fecharArquivos(fitas);
}
