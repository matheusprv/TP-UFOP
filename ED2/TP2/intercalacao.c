#include "intercalacao.h"

void gerarFitas(Fita * fitas){
    for(int i = 0; i < 40; i++){
        fitas[i].n_blocos = 0;
        //Define o tipo de fita
        fitas[i].tipo = i < 20 ? ENTRADA : SAIDA;

        char nomeArquivo[20];
        sprintf(nomeArquivo, "fitas/fita_%d.bin", i+1);
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
    FILE * arq = fopen(infoOrdenacao->nomeArquivo, "rb");
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
    int numItensDoBloco = 0;

    //Gerando um vetor que possui a quantidade de itens de cada bloco da fita
    //O vetor comeca com zero posicoes e vai sendo incrementado ao possui mais blocos na fita
    for(int i = 0; i < 20; i++){
        fitas[i].qtdItensBloco = malloc(0);
    }

    for(int i = 0; i < qtdItensQueFaltam; i++){
        //retira o primeiro do vetor e escreve na fita
        registroRetirado = blocoPorSubstituicao[0].registro;
        fwrite(&registroRetirado, sizeof(TipoRegistro), 1, fitas[fitaAtual%20].arq);
        numItensDoBloco++;

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
            fitas[fitaAtual].qtdItensBloco = realloc(fitas[fitaAtual].qtdItensBloco, fitas[fitaAtual].n_blocos * sizeof(int));
            fitas[fitaAtual].qtdItensBloco[fitas[fitaAtual].n_blocos-1] = numItensDoBloco;

            fitaAtual++; //vai para proxima fita]
            numItensDoBloco = 0;
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

    //Verificando a quantidade de blocos que serao lidos
    int qtdBlocos = (int) ceil(infoOrdenacao->quantidade / 20.0);
    int qtdItensALer, qtdItensQueFaltam = infoOrdenacao->quantidade;

    int i;
    //Transferindo os dados para as fitas
    for(i = 0; i < qtdBlocos; i++){
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

    for(i = 0; i < 20; i++){
        fitas[i].qtdItensBloco = malloc(fitas[i].n_blocos * sizeof(int));

        for (int j = 0; j < fitas[i].n_blocos; j++)
            fitas[i].qtdItensBloco[j] = 20;
    }

    int fitaDoUltimoBloco = (qtdBlocos % 20) == 0 ? 19 : (qtdBlocos % 20) - 1;
    int blocos = fitas[fitaDoUltimoBloco].n_blocos; //num blocos da fita do ultimo bloco
    fitas[fitaDoUltimoBloco].qtdItensBloco[blocos-1] = infoOrdenacao->quantidade % 20 == 0 ? 20 : infoOrdenacao->quantidade % 20;

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
    for(int i = 0; i < qtdFitas; i++){
        if(intercalacao[i].fitaAtiva)
            return false;
    }

    return true;
}

//Le o primeiro item dos blocos e retorna a posicao do item de menor elemento
void lerPrimeirosDados(int inicio, Intercalacao * fitasIntercalacao, Fita * fitas, int qtdFitas){
    for(int i = 0; i < qtdFitas; i++ ){
        fread(&fitasIntercalacao[i].dadoLido, sizeof(TipoRegistro), 1, fitas[i + inicio].arq);
        fitasIntercalacao[i].qtdItensLidos++;
    }
}

int procurarMenorValor(Intercalacao * dadosIntercalacao, int qtdFitas){
    TipoRegistro temp;
    int indexMenorItem=qtdFitas;

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
        if(dadosIntercalacao[i].fitaAtiva && temp.nota > dadosIntercalacao[i].dadoLido.nota){
            indexMenorItem = i;
            temp = dadosIntercalacao[i].dadoLido;
        }
    }
    return indexMenorItem;
}

void escreverDadosOrdenados(Fita * fitas, InfoOrdenacao * infoOrdenacao, int fitaSaida){
    int qtdItensALer = infoOrdenacao->quantidade;
    TipoRegistro dadosLeitura[20];
    FILE * arqDestino = fopen(infoOrdenacao->nomeArquivo, "wb");
    
    while(qtdItensALer > 0){
        int qtdProximaLeitura = qtdItensALer > 20 ? 20 : qtdItensALer; 
        qtdItensALer -= qtdProximaLeitura;
        fread(dadosLeitura, sizeof(TipoRegistro), qtdProximaLeitura, fitas[fitaSaida].arq);
        fwrite(dadosLeitura, sizeof(TipoRegistro), qtdProximaLeitura, arqDestino);
    }

    fclose(arqDestino);
}

void intercalarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao){

    enum TipoFita tipoFitaLeitura = ENTRADA;
    int entrada, saida;
    //marca qual sera a fita de saida que recebera o bloco resultante da passada atual da intercalacao
    int fitaSaida;
    
    int passada;
    
    //Verificando a quantidade total de blocos gerados
    int qtdBlocos = 0;

    for (int i = 0; i < 20; i++)
        qtdBlocos += fitas[i].n_blocos;
    
    //Executando até que tenhamos somente um bloco
    while(qtdBlocos > 1){
        if(tipoFitaLeitura == ENTRADA){
            entrada = 0; saida = 20;
        }
        else{
            entrada = 20; saida = 0;
        }       

        int qtdFitas;
        passada = 1;

        //executa todas as passadas de intercalacao nas fitas de entrada
        do{
            //Verificando a quantidade de fitas com blocos que irao participar dessa passada, 
            //afim de evitar que fitas sem conteudo sejam varridas
            qtdFitas = 0;
            for (int i = entrada; i < entrada+20; i++)
                if(fitas[i].n_blocos >= passada)
                    qtdFitas++;

            Intercalacao * dadosIntercalacao = gerarFitasIntercalacao(qtdFitas);

            fitaSaida = saida + passada - 1;

            //Lendo o primeiro registro de cada bloco
            lerPrimeirosDados(entrada, dadosIntercalacao, fitas, qtdFitas);

            int posicaoMenorNota;

            //representa 1 passada
            //Lendo todos os dados e escrevendo o que tiver a menor chave
            while(todosOsDadosLidos(dadosIntercalacao, qtdFitas) == false){
                posicaoMenorNota = procurarMenorValor(dadosIntercalacao, qtdFitas);

                //Escrevendo o item de menor chave na fita de saida
                fwrite(&dadosIntercalacao[posicaoMenorNota].dadoLido, sizeof(TipoRegistro), 1, fitas[fitaSaida].arq);

                //desativando a fita caso todos os seus itens ja tenham sido lidos
                if(dadosIntercalacao[posicaoMenorNota].qtdItensLidos == fitas[entrada+posicaoMenorNota].qtdItensBloco[passada-1]){
                    dadosIntercalacao[posicaoMenorNota].fitaAtiva = false;
                    //decrementando o numero de blocos daquela fita, tendo em vista que ela ira virar uma fita de saida posteriormente
                    fitas[entrada+posicaoMenorNota].n_blocos--;
                }

                //Lendo o proximo item da fita onde o registro retirado eh proveniente, ja que a fita ainda estiver ativa
                else{
                    fread(&dadosIntercalacao[posicaoMenorNota].dadoLido, sizeof(TipoRegistro), 1, fitas[posicaoMenorNota+entrada].arq);
                    dadosIntercalacao[posicaoMenorNota].qtdItensLidos++;
                }
            }

            passada++;
            fitas[fitaSaida].n_blocos++;

            free(dadosIntercalacao);
        }while(qtdFitas != 0);

        //recalcula qtd de blocos restantes
        qtdBlocos = passada-1;

        tipoFitaLeitura = tipoFitaLeitura == ENTRADA ? SAIDA : ENTRADA;

    }

    //copia saida final para o arquivo quer se quer ordenadar
    escreverDadosOrdenados(fitas, infoOrdenacao, fitaSaida);

}

void intercalacao_balanceada(InfoOrdenacao * infoOrdenacao){
    
    Fita fitas[40];
    gerarFitas(fitas);

    if(infoOrdenacao->metodo == BALANCEADA_BLOCO_OI)
        gerarBlocos(fitas, infoOrdenacao);
    else
        gerarSelecaoSubstituicao(fitas, infoOrdenacao);

    setPointeirosInicio(fitas);

    intercalarBlocos(fitas, infoOrdenacao);

    fecharArquivos(fitas);
}
