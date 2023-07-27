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
        fitas[i].tipo = i < 20 ? ENTRADA : SAIDA;

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
    RegistroParaSubstituicao blocoPorSubstituicao[20]; //Memoria Interna

    int qtdItensALer, qtdItensQueFaltam = infoOrdenacao->quantidade;

    qtdItensALer = qtdItensQueFaltam >= 20 ? 20 : qtdItensQueFaltam;
    qtdItensQueFaltam -= qtdItensALer;

    //vetor auxiliar de registros para nao precisar ler 1 por 1 no arquivo
    TipoRegistro aux[20];

    fread(aux, sizeof(TipoRegistro), qtdItensALer, arq);

    //copiando os registros do vetor auxiliar para o vetor de blocos
    for (int i = 0; i < 20; i++)
        blocoPorSubstituicao[i].registros = aux[i];

    //ordenar essa primeira leva de registros

    for(int i = 0; i < qtdItensQueFaltam; i++){
        //retira o primeiro do vetor e escreve na fita (criar variavel auxiliar para controlar em qual fita esta escrevendo)
        //le o proximo registro do provaoaleatorio e verifica se e menor que o ultimo que saiu
    }

    fclose(arq);
}

void gerarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao){

    FILE * arq = fopen(infoOrdenacao->nomeArquivo, "rb");
    TipoRegistro registrosInterno [20]; //Memoria Interna

    //Verificando a quantidade de blocos que serão lidos
    int qtdBlocos = (int) ceil(infoOrdenacao->quantidade / 20.0);
    int qtdItensALer, qtdItensQueFaltam = infoOrdenacao->quantidade;

    //Transferindo os dados para as fitas
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

    fclose(arq);
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
        fitasIntercalacao[i].fitaAtiva = true;
    }

    return fitasIntercalacao;
}

bool todosOsDadosLidos(Intercalacao * intercalacao, int qtdFitas){
    //Verifica se todos os dados dos blocos foram lidos
    for(int i = 0; i < 20; i++){
        if(intercalacao[i].fitaAtiva)
            return false;
    }

    return true;
}

//Le o primeiro item dos blocos e retorna a posicao do item de menor elemento
int lerPrimeirosDados(int inicio, Intercalacao * fitasIntercalacao, Fita * fitas){
    fread(&fitasIntercalacao[0].dadoLido, sizeof(TipoRegistro), 1, fitas[inicio].arq);
    int indexMenorRegistro = inicio;

    for(int i = inicio + 1; i < inicio + 20; i++ ){
        fread(&fitasIntercalacao[i].dadoLido, sizeof(TipoRegistro), 1, fitas[i + inicio].arq);
        if(fitasIntercalacao[i].dadoLido.Chave < fitasIntercalacao[indexMenorRegistro].dadoLido.Chave)
            indexMenorRegistro = i;
    }

    return indexMenorRegistro;
}

int procurarMenorValor(Intercalacao * dadosIntercalacao, int qtdFitas){
    TipoRegistro temp;
    int indexMenorItem;

    //procurando a primeira fita ativa
    for(int i = 0; i < qtdFitas; i++){
        if(dadosIntercalacao[i].fitaAtiva){
            indexMenorItem = i;
            temp = dadosIntercalacao[i].dadoLido;
            break;
        }
    }

    //Procurando no restante das fitas o dado com a menor nota
    for(int i = indexMenorItem + 1; i < qtdFitas; i++){
        if(temp.nota < dadosIntercalacao[i].dadoLido.nota){
            indexMenorItem = i;
            temp = dadosIntercalacao[i].dadoLido;
        }
    }
    return indexMenorItem;
}

void intercalarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao){

    enum TipoFita tipoFitaLeitura = ENTRADA;
    int passada = 0;
    int arqLeitura;
    
    //Verificando a quantidade de blocos que serao lidos, sendo que no inicio, cada bloco tera, no maximo, 20 itens
    int qtdBlocos = (int) ceil(infoOrdenacao->quantidade / 20.0);

    while(qtdBlocos > 1){
        //Verificando a quantidade de fitas com registros, afim de evitar que fitas sem conteudo sejam varridas
        int qtdFitas = qtdBlocos < 20 ? qtdBlocos : 20;

        Intercalacao * dadosIntercalacao = gerarFitasIntercalacao(qtdFitas);

        //Lendo o primeiro registro de cada bloco
        int fitaEntrada = tipoFitaLeitura == ENTRADA ? 0 : 20;
        int fitaSaida   = (tipoFitaLeitura == 0 ? 20 : 0) + passada;
        int indexMenorRegistro = lerPrimeirosDados(fitaEntrada, dadosIntercalacao, fitas);

        //Lendo todos os dados e escrevendo o que tiver a menor chave
        while(todosOsDadosLidos(dadosIntercalacao, qtdFitas) == false){
            //Escrever o item de menor chave na fita de saida e desativando a mesma caso os seus 20 itens ja foram lidos
            fwrite(&dadosIntercalacao[indexMenorRegistro].dadoLido, sizeof(TipoRegistro), 1, fitas[fitaSaida].arq);
            if(dadosIntercalacao[indexMenorRegistro].qtdItensLidos == 20) dadosIntercalacao[indexMenorRegistro].fitaAtiva = false;

            //Lendo o proximo item da fita onde o registro retirado eh proveniente, mas somente se a fita ainda estiver ativa
            if(dadosIntercalacao[indexMenorRegistro].fitaAtiva){
                fread(&dadosIntercalacao[indexMenorRegistro].dadoLido, sizeof(TipoRegistro), 1, fitas[indexMenorRegistro].arq);
                dadosIntercalacao[indexMenorRegistro].qtdItensLidos ++;
            }
        }

        //Acrescentando mais um na quantidade de blocos da fita de saida 

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
