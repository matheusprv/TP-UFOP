#include "intercalacao.h"

void gerarFitas(Fita * fitas){
    for(int i = 0; i < 40; i++){
        fitas[i].n_blocos = 0;
        //Define o tipo de fita
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

bool todosMarcados(RegistroParaSubstituicao* registros){
    for (int i = 0; i < 20; i++)
        if(registros[i].marcado == false)
            return false;
    
    return true;
}

void desmarcarRegistros(RegistroParaSubstituicao* registros){
    for(int i = 0; i < 20; i++)
        registros[i].marcado = false;
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

    //copiando os registros do vetor auxiliar para o vetor que representa a memoria interna
    for (int i = 0; i < 20; i++){
        blocoPorSubstituicao[i].registro = aux[i];
        blocoPorSubstituicao[i].marcado = false;
    }

    //ordenar essa primeira leva de registros, construindo/ordenando o heap
    heap_sort(blocoPorSubstituicao, 20);

    int fitaAtual = 0; //fita atual de entrada
    TipoRegistro registroRetirado;
    RegistroParaSubstituicao proxRegistro;

    for(int i = 0; i < qtdItensQueFaltam; i++){
        //retira o primeiro do vetor e escreve na fita
        registroRetirado = blocoPorSubstituicao[0].registro;
        fwrite(&registroRetirado, sizeof(TipoRegistro), 1, fitas[fitaAtual%20].arq);

        //le o proximo registro do provao aleatorio e verifica se e menor que o ultimo que saiu
        fread(&proxRegistro.registro, sizeof(TipoRegistro), 1, arq);
        
        if(proxRegistro.registro.nota < registroRetirado.nota)
            proxRegistro.marcado = true;
        else
            proxRegistro.marcado = false;

        //propriedade do heap:
        //passando o ultimo elemento do vetor para a raiz, para refazer o heap depois
        blocoPorSubstituicao[0] = blocoPorSubstituicao[19];
        //inserindo o registro na memoria interna
        blocoPorSubstituicao[19] = proxRegistro;

        if(todosMarcados(blocoPorSubstituicao)){
            desmarcarRegistros(blocoPorSubstituicao);
            fitas[fitaAtual].n_blocos++;
            fitaAtual++; //vai para proxima fita
        }

        //refazendo o heap
        heap_refaz(blocoPorSubstituicao, 0, 19);        
    }

    //escrever o resto dos itens presentes na memoria interna
    for(int i = 0; i < 20; i++)
        aux[i] = blocoPorSubstituicao[i].registro;

    fwrite(aux, sizeof(TipoRegistro), 20, arq);
    fitas[fitaAtual%20].n_blocos++;

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
        fitas[i%20].n_blocos ++;
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
                dadosIntercalacao[indexMenorRegistro].qtdItensLidos++;
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
