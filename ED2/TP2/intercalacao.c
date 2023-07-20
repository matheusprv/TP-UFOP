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

        char nomeArquivo[20];
        sprintf(nomeArquivo, "fita_%d.bin", i+1);
        fitas[i].arq = fopen(nomeArquivo, "wb+");
    }
}

void fecharArquivos(Fita * fitas){
    for(int i = 0; i < 40; i++){
        fclose(fitas[i].arq);
    }
}

void gerarSelecaoSubstituicao(Fita * fitas, InfoOrdenacao *infoOrdenacao){
    FILE * arq = fopen("PROVAO_ALEATORIO.bin", "rb");
    BlocoPorSubstituicao blocoPorSubstituicao; //Memoria Interna

    int qtdItensALer, qtdItensQueFaltam = infoOrdenacao->quantidade;

    qtdItensALer = qtdItensQueFaltam >= 20 ? 20 : qtdItensQueFaltam;
    qtdItensQueFaltam -= qtdItensALer;

    fread(blocoPorSubstituicao.registros, sizeof(TipoRegistro), qtdItensALer, arq);

    //ordenar essa primeira leva de registros

    for(int i = 0; i < qtdItensQueFaltam; i++){
        //retira o primeiro do vetor e escreve na fita (criar variavel auxiliar para controlar em qual fita esta escrevendo)
        //le o proximo registro do provaoaleatorio e verifica se e menor que o ultimo que saiu
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

void setPointeirosInicio(Fita * fitas){
    for(int i = 0; i < 40; i++){
        fseek(fitas[i].arq, 0, SEEK_SET);   
    }
}

Intercalacao * gerarFitasIntercalacao(int qtdFitas){
    Intercalacao * fitasIntercalacao = (Intercalacao*) malloc(qtdFitas * sizeof(Intercalacao));
    for(int i = 0; i < qtdFitas; i++){
        fitasIntercalacao[i].qtdItensLidos = 0;
    }

    return fitasIntercalacao;
}

bool todosOsDadosLidos(Intercalacao * intercalacao, int qtdFitas){
    //Verifica se todos os dados dos blocos foram lidos
    for(int i = 0; i < 20; i++){
        if(intercalacao[i].qtdItensLidos != 20)
            return false;
    }

    return true;
}

//Le o primeiro item dos blocos e retorna a posicao do item de menor elemento
int lerPrimeirosDados(int inicio, Intercalacao * fitasIntercalacao, Fita * fitas){
    fread(&fitasIntercalacao[0].dadoLido, sizeof(TipoRegistro), 1, fitas[inicio].arq);
    int index_menor_registro = inicio;

    for(int i = inicio + 1; i < inicio + 20; i++ ){
        fread(&fitasIntercalacao[i].dadoLido, sizeof(TipoRegistro), 1, fitas[i + inicio].arq);
        if(fitasIntercalacao[i].dadoLido.Chave < fitasIntercalacao[index_menor_registro].dadoLido.Chave)
            index_menor_registro = i;
    }

    return index_menor_registro;
}

int procurarMenorValor(Intercalacao * fitasIntercalacao, int qtdFitas){
    for(int i = 0; i < qtdFitas; i++){

    }
    return 0;
}

void intercalarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao){

    enum TipoFita tipo_fita = ENTRADA;
    int passada = 0;
    int arqLeitura;
    
    //Verificando a quantidade de blocos que serao lidos
    int qtdBlocos = (int) ceil(infoOrdenacao->quantidade / 20.0);

    while(qtdBlocos > 1){
        //Verificando a quantidade de fitas com registros, afim de evitar que fitas sem conteudo sejam varridas
        int qtdFitas = qtdBlocos < 20 ? qtdBlocos : 20;

        Intercalacao * fitasIntercalacao = gerarFitasIntercalacao(qtdFitas);

        //Lendo o primeiro registro de cada bloco
        int inicio = tipo_fita == ENTRADA ? 0 : 20;
        int fitaEscrever = (tipo_fita == 0 ? 20 : 0) + passada;
        int index_menor_registro = lerPrimeirosDados(inicio, fitasIntercalacao, fitas);

        //Escrever o item de menor chave
        fwrite(&fitasIntercalacao[index_menor_registro].dadoLido, sizeof(TipoRegistro), 1, fitas[fitaEscrever].arq);

        //Lendo todos os dados e escrevendo o que tiver a menor chave
        while(todosOsDadosLidos(fitasIntercalacao, qtdFitas) == false){
            // TODO: Verificar se o bloco ja foi todo lido ou nao
            arqLeitura = index_menor_registro + (tipo_fita == ENTRADA ? 0 : 20);
            fread(&fitasIntercalacao[index_menor_registro].dadoLido, sizeof(TipoRegistro), 1, fitas[arqLeitura].arq);


            fwrite(&fitasIntercalacao[index_menor_registro].dadoLido, sizeof(TipoRegistro), 1, fitas[fitaEscrever].arq);
        }

        passada++;
    }



}

void intercalacao_balanceada(InfoOrdenacao * infoOrdenacao){
    
    Fita fitas[40];
    gerarFitas(fitas);

    gerarBlocos(fitas, infoOrdenacao);

    setPointeirosInicio(fitas);

    intercalarBlocos(fitas, infoOrdenacao);


    fecharArquivos(fitas);
}
